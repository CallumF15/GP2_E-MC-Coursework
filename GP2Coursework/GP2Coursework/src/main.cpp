#include <iostream>
#include <GL/glew.h>
//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <gl/GLU.h>
#endif

#include <vector>

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
const std::string MODEL_PATH = "models/";
#elif __APPLE__
const std::string ASSET_PATH;
const std::string SHADER_PATH;
const std::string TEXTURE_PATH;
const std::string FONT_PATH;
const std::string MODEL_PATH;
#else
const std::string ASSET_PATH="/assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
const std::string MODEL_PATH = "models/";
#endif

//Our headers
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "FBXLoader.h"

#include "primitiveType.h"
#include "SkyBox.h"

Camera * c = new Camera();

//SDL Window
SDL_Window * window = NULL;
//SDL GL Context
SDL_GLContext glcontext = NULL;

//Window Width
const int WINDOW_WIDTH = 1100;
//Window Height
const int WINDOW_HEIGHT = 900;

bool running = true;


vec4 ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

//std::vector<GameObject*> displayList;
GameObject * mainCamera;
GameObject * mainLight;
GameObject * secondLight;
GameObject * skyBoxObject = NULL;

primitiveType* type;
GameObject * house;


void CheckForErrors()
{
	GLenum error;
	do{
		error = glGetError();
	} while (error != GL_NO_ERROR);
}

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow(
		"Lab 6",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);
}

void CleanUp()
{
	if (skyBoxObject)
	{
		skyBoxObject->destroy();
		delete skyBoxObject;
		skyBoxObject = NULL;
	}

	auto iter = type->displayList.begin();
	while (iter != type->displayList.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete (*iter);
			(*iter) = NULL;
			iter = type->displayList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	type->displayList.clear();

	// clean up, reverse order!!!
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


//Function to initialise OpenGL
void initOpenGL()
{
	//Ask for version 3.2 of OpenGL

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to go
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Function to set/reset viewport
void setViewport(int width, int height)
{

	//make sure height is always above 1
	if (height == 0) {
		height = 1;
	}


	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void createSkyBox()
{

	Vertex triangleData[] = {
			{ vec3(-50.0f, 50.0f, 50.0f) },// Top Left
			{ vec3(-50.0f, -50.0f, 50.0f) },// Bottom Left
			{ vec3(50.0f, -50.0f, 50.0f) }, //Bottom Right
			{ vec3(50.0f, 50.0f, 50.0f) },// Top Right

			{ vec3(-50.0f, 50.0f, -50.0f) },// Top Left
			{ vec3(-50.0f, -50.0f, -50.0f) },// Bottom Left
			{ vec3(50.0f, -50.0f, -50.0f) }, //Bottom Right
			{ vec3(50.0f, 50.0f, -50.0f) }// Top Right
	};


	GLuint indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		3, 2, 6,
		6, 7, 3,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// left
		4, 0, 3,
		3, 7, 4,
		// right
		1, 5, 6,
		6, 2, 1,


	};



	////creat mesh and copy in

	Mesh * pMesh = new Mesh();
	pMesh->init();

	pMesh->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
	pMesh->copyIndexData(36, sizeof(int), (void**)indices);

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 0.0f);
	//load textures and skybox material + Shaders
	SkyBox *material = new SkyBox();
	material->init();

	std::string vsPath = ASSET_PATH + SHADER_PATH + "/skyVS.glsl";
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/skyFS.glsl";
	material->loadShader(vsPath, fsPath);

	std::string posZTexturename = ASSET_PATH + TEXTURE_PATH + "sky.png";
	std::string negZTexturename = ASSET_PATH + TEXTURE_PATH + "sky.png";
	std::string posXTexturename = ASSET_PATH + TEXTURE_PATH + "sky.png";
	std::string negXTexturename = ASSET_PATH + TEXTURE_PATH + "sky.png";
	std::string posYTexturename = ASSET_PATH + TEXTURE_PATH + "sky.png";
	std::string negYTexturename = ASSET_PATH + TEXTURE_PATH + "sky.png";

	material->loadCubeTexture(posZTexturename, negZTexturename, posXTexturename, negXTexturename, posYTexturename, negYTexturename);
	//create gameobject but don't add to queue!
	skyBoxObject = new GameObject();
	skyBoxObject->setMaterial(material);
	skyBoxObject->setTransform(t);
	skyBoxObject->setMesh(pMesh);

	CheckForErrors();
}

void Initialise()
{
	createSkyBox();

	type = new primitiveType();

	

	mainCamera = new GameObject();
	mainCamera->setName("MainCamera");

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 2.0f);
	mainCamera->setTransform(t);

	c->setAspectRatio((float)(WINDOW_WIDTH / WINDOW_HEIGHT));
	c->setFOV(45.0f);
	c->setNearClip(0.1f);
	c->setFarClip(1000.0f);

	mainCamera->setCamera(c);
	type->displayList.push_back(mainCamera);

	mainLight = new GameObject();
	mainLight->setName("MainLight");

	secondLight = new GameObject();
	secondLight->setName("secondLight");

	t = new Transform();
	t->setPosition(0.0f, 0.0f, 0.0f);
	mainLight->setTransform(t);

	Light * light = new Light();
	mainLight->setLight(light);
	//mainLight->getLight()->setDirection(-90, 0, 0);
	type->displayList.push_back(mainLight);

	Light * light2 = new Light();
	secondLight->setLight(light2);
	secondLight->getLight()->setDirection(-90, 0, 0);
	type->displayList.push_back(secondLight);


	std::string modelPath = ASSET_PATH + MODEL_PATH + "sword2.fbx";
	GameObject * go = loadFBXFromFile(modelPath);

//std::string modelPath = ASSET_PATH + MODEL_PATH + "fachwerkhaus2_2_LOD.fbx";
	//GameObject * go = loadFBXFromFile(modelPath);
	//type->createPrimitive(cube, vec3(1, 1, 1), vec3(0, 0, 0), vec3(10, 10, 10));
	//type->createPrimitive(cube, vec3(10, 1, 1), vec3(0, 0, 0), vec3(5, 5, 5));

	type->setModelsBump("sword2.fbx", "sword2_C.png", "sword_S.png", "sword_N.png");
	type->setModelsBump("armoredrecon.fbx", "armoredrecon_diff.png", "armoredrecon_spec.png", "armoredrecon_N.png");
	type->setModelsBump("2h_axe.fbx", "2h_axeD.png", "2h_axeS.png", "2h_axeN.png");
	type->setModelsBump("sword2.fbx", "sword2_C.png", "sword_S.png", "sword_N.png");
	type->setModelsBump("fachwerkhaus2_2_anderer_style.fbx", "LOD_f_2.png", "LOD_f_2.png", "LOD_f_2.png");
type->setModelsBump("2h_axe.fbx", "2h_axeD.png", "2h_axeS.png", "2h_axeN.png");

	
	//type->setModelsBump("armoredrecon.fbx", "armoredrecon_diff.png", "armoredrecon_spec.png", "armoredrecon_N.png");
	type->setTransformation(vec3(-1, 1, -10), vec3(-90, 45, 0), vec3(0.001, 0.001, 0.001));//sword
	
	type->setTransformation(vec3(-5, 0, -10), vec3(0, 0, 0), vec3(1, 1, 1));//car
	type->setTransformation(vec3(-10, 1, -10), vec3(-90, 1, 1), vec3(0.01, .01, .01));//ax
	type->setTransformation(vec3(-3, 8, -10), vec3(-90, 45, 0), vec3(0.001, 0.001, 0.001));//sword2
	type->setTransformation(vec3(-18,1, -9), vec3(-89.35,0, 0), vec3(0.01, 0.01, 0.01));//house
	type->setTransformation(vec3(-15, 1, -10), vec3(-90, 1, 1), vec3(0.01, 0.01, 0.01));//ax
	
	type->loadModels(bump);
	
	primitiveType* parralaxType = new primitiveType();
	parralaxType->CreatePrim("pavement_color.png", "pavement_spec.png", "pavement_normal.png", cube, vec3(-10, 0, -10), vec3(0, 0, 0), vec3(40, 0, 20));
	parralaxType->setPrimitiveTexture("pavement_color.png","pavement_spec.png","pavement_normal.png");
	parralaxType->createPrimitive(cube, vec3(-10, 0, -10), vec3(0, 0, 0), vec3(40, 0, 20));
	
	parralaxType->setTransformation(vec3(-15, 0, -10), vec3(0, 0, 0), vec3(1, 1, 1));
	parralaxType->loadModels(parralax);
	type->setDisplaylist(parralaxType->getDisplayList());

	//primitiveType* primitive = new primitiveType();

	//primitive->CreatePrim("pavement_color.png", "pavement_spec.png", "pavement_normal.png", cube, vec3(-10, 0, -10), vec3(0, 0, 0), vec3(40, 0, 20));
	//primitive->setPrimitiveTexture("pavement_color.png", "pavement_spec.png", "pavement_normal.png");
	//parralaxType->createPrimitive(cube, vec3(-10, 0, -10), vec3(0, 0, 0), vec3(40, 0, 20));
	
}


//Function to update the game state
void update()
{
	skyBoxObject->update();
	//alternative sytanx
	for (auto iter = type->displayList.begin(); iter != type->displayList.end(); iter++)
	{
		(*iter)->update();
	}
}

void renderGameObject(GameObject * pObject)
{
	if (!pObject)
		return;

	pObject->render();

	Mesh * currentMesh = pObject->getMesh();
	Transform * currentTransform = pObject->getTransform();
	Material * currentMaterial = (Material*)pObject->getMaterial();

	if (currentMesh && currentMaterial && currentTransform)
	{
		currentMaterial->bind();
		currentMesh->bind();

		GLint MVPLocation = currentMaterial->getUniformLocation("MVP");
		GLint ModelLocation = currentMaterial->getUniformLocation("Model");
		GLint ambientMatLocation = currentMaterial->getUniformLocation("ambientMaterialColour");
		GLint ambientLightLocation = currentMaterial->getUniformLocation("ambientLightColour");
		GLint diffuseMatLocation = currentMaterial->getUniformLocation("diffuseMaterialColour");
		GLint diffuseLightLocation = currentMaterial->getUniformLocation("diffuseLightColour");
		GLint lightDirectionLocation = currentMaterial->getUniformLocation("lightDirection");
		GLint specularMatLocation = currentMaterial->getUniformLocation("specularMaterialColour");
		GLint specularLightLocation = currentMaterial->getUniformLocation("specularLightColour");
		GLint specularpowerLocation = currentMaterial->getUniformLocation("specularPower");
		GLint cameraPositionLocation = currentMaterial->getUniformLocation("cameraPosition");
		GLint diffuseTextureLocation = currentMaterial->getUniformLocation("diffuseMap");
		GLint specTextureLocation = currentMaterial->getUniformLocation("specMap");
		GLint bumpTextureLocation = currentMaterial->getUniformLocation("bumpMap");
		GLint heightTextureLocation = currentMaterial->getUniformLocation("heightMap");

		Camera * cam = mainCamera->getCamera();
		Light* light = mainLight->getLight();


		mat4 MVP = cam->getProjection()*cam->getView()*currentTransform->getModel();
		mat4 Model = currentTransform->getModel();

		vec4 ambientMaterialColour = currentMaterial->getAmbientColour();
		vec4 diffuseMaterialColour = currentMaterial->getDiffuseColour();
		vec4 specularMaterialColour = currentMaterial->getSpecularColour();
		float specularPower = currentMaterial->getSpecularPower();

		vec4 diffuseLightColour = light->getDiffuseColour();
		vec4 specularLightColour = light->getSpecularColour();
		vec3 lightDirection = light->getDirection();

		//vec3 cameraPosition = mainCamera->getTransform()->getPosition();
		vec3 cameraPosition = c->getPosition();

		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform4fv(ambientMatLocation, 1, glm::value_ptr(ambientMaterialColour));
		glUniform4fv(ambientLightLocation, 1, glm::value_ptr(ambientLightColour));

		glUniform4fv(diffuseMatLocation, 1, glm::value_ptr(diffuseMaterialColour));
		glUniform4fv(diffuseLightLocation, 1, glm::value_ptr(diffuseLightColour));
		glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));

		glUniform4fv(specularMatLocation, 1, glm::value_ptr(specularMaterialColour));
		glUniform4fv(specularLightLocation, 1, glm::value_ptr(specularLightColour));

		glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cameraPosition));
		glUniform1f(specularpowerLocation, specularPower);

		glUniform1i(diffuseTextureLocation, 0);
		glUniform1i(specTextureLocation, 1);
		glUniform1i(bumpTextureLocation, 2);
		glUniform1i(heightTextureLocation, 3);

		glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);

		currentMaterial->unbind();
	}

	for (int i = 0; i < pObject->getChildCount(); i++)
	{
		renderGameObject(pObject->getChild(i));
	}
}

void renderSkyBox()
{
	skyBoxObject->render();

	Mesh * currentMesh = skyBoxObject->getMesh();
	SkyBox * currentMaterial = (SkyBox*)skyBoxObject->getMaterial();
	if (currentMesh && currentMaterial)
	{
		Camera * cam = mainCamera->getCamera();

		currentMaterial->bind();
		currentMesh->bind();

		GLint cameraLocation = currentMaterial->getUniformLocation("cameraPos");
		GLint viewLocation = currentMaterial->getUniformLocation("view");
		GLint projectionLocation = currentMaterial->getUniformLocation("projection");
		GLint cubeTextureLocation = currentMaterial->getUniformLocation("cubeTexture");

		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam->getProjection()));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam->getView()));
		glUniform4fv(cameraLocation, 1, glm::value_ptr(mainCamera->getTransform()->getPosition()));
		glUniform1i(cubeTextureLocation, 0);

		glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);

		currentMaterial->unbind();
	}
	CheckForErrors();
}

//Function to render(aka draw)
void render()
{
	//old imediate mode!
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSkyBox();

	//alternative sytanx
	for (auto iter = type->displayList.begin(); iter != type->displayList.end(); iter++)
	{
		renderGameObject((*iter));
	}

	SDL_GL_SwapWindow(window);
}

//Main Method
int main(int argc, char * arg[])
{


	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}

	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)& (imageInitFlags)) != imageInitFlags) {
		std::cout << "ERROR SDL_Image Init " << IMG_GetError() << std::endl;
		// handle error
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError();
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
	//Call our InitOpenGL Function
	initOpenGL();
	CheckForErrors();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	Initialise();

	//Value to hold the event generated by SDL
	SDL_Event event;
	//Game Loop
	while (running)
	{
		//While we still have events in the queue
		while (SDL_PollEvent(&event)) {

			switch (event.type){

			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){

				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w:
					c->movement(FORWARD);
					//c->setMovementType(FORWARD);
					break;
				case SDLK_s:
					c->movement(BACKWARD);
					break;
				case SDLK_a:
					c->movement(STRAFE_LEFT);
					break;
				case SDLK_d:
					c->movement(STRAFE_RIGHT);
					break;
				case SDLK_r:
					c->movement(UP);
					break;
				case SDLK_f:
					c->movement(DOWN);
					break;
				case SDLK_l:
					c->movement(RESET);
					break;
				}
			case SDL_MOUSEMOTION:
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;
				glm::vec2 mousePos = glm::vec2(mouseX, mouseY);

				c->mouseUpdate(mousePos);

				//add code to get came working with the cursor centred to middle of the screen
				//SDL_WarpMouseInWindow(window, 320, 240);
				break;
			}
		}

		//current_time = SDL_GetTicks();
		//elapsed_time = current_time - last_time; //on calcule le temps écoulé depuis la dernière image
		//last_time = current_time;


		update();
		render();
	}


	CleanUp();

	return 0;
}