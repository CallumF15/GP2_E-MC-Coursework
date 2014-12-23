///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class was implemented by Callum Flannagan. Contributions were made by Mathew McGerty & Conor Johnston //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <GL/glew.h>
//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
const std::string ASSET_PATH = "/assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
const std::string MODEL_PATH = "models/";
#endif

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

#include "SplashScreen.h"
#include <vector>

GameObject * mainCamera;
GameObject * mainLight;
GameObject * skyBoxObject = NULL;

primitiveType* type;
PostProcessing postProcessor;

int switchNumber = 0;
colourFilterType colourtype;
mat3 selectedColour;


//Constructor
SplashScreen::SplashScreen()
{

}

//Destructor
SplashScreen::~SplashScreen(){

}

//This is where all the content is loaded into the game.
//Used for setting up GameObjects, setting their translations/positions
//Used to load up multiple models by calling another class.
//Also used to intialize the postprocessing.
//Adds all GameObjects into a vector array.
void SplashScreen::LoadContent(){

	std::string vsPath = ASSET_PATH + SHADER_PATH + "/passThroughVS.glsl";
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/colourFilterPostFS.glsl";  //change this to boxFilterBlurFS for blur

	postProcessor.init(1024, 768, vsPath, fsPath);

	createSkyBox();

	type = new primitiveType();

	mainCamera = new GameObject();
	mainCamera->setName("MainCamera");

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 2.0f);
	mainCamera->setTransform(t);

	Camera * c = new Camera();
	c->setAspectRatio((float)(1024 / 768));
	c->setFOV(45.0f);
	c->setNearClip(0.1f);
	c->setFarClip(1000.0f);

	mainCamera->setCamera(c);
	displayList.push_back(mainCamera);

	mainLight = new GameObject();
	mainLight->setName("MainLight");

	t = new Transform();
	t->setPosition(45.0f, 41.0f, 43.0f);
	mainLight->setTransform(t);

	Light * light = new Light();
	mainLight->setLight(light);
	displayList.push_back(mainLight);

	//Model loading
	type->setModelsBump("plane.fbx", "pavement_color.png", "pavement_spec.png", "pavement_normal.png");
	type->setTransformation(vec3(-10, -1, 0), vec3(-90, 0, 0), vec3(1, 1, 1));
	type->loadModels(bump);

	primitiveType* pointType = new primitiveType();
	pointType->setModelsBump("shield_deco3.fbx", "shield_C.png", "shield_D.png", "shield_N.png");//shield 1//
	pointType->setModelsBump("constuct_bridge.fbx", "s_12.png", "s_12S.png", "s_12N.png");//bridge//
	pointType->setModelsBump("constuct_shild_A.fbx", "p_1.png", "p_1S.png", "s_12N.png");//sign//
	pointType->setModelsBump("constuct_understand_wood.fbx", "u_8.png", "u_8S.png", "u_8N.png");
	pointType->setModelsBump("2h_axe.fbx", "2h_axe.png", "2h_axeS.png", "2h_axeN.png");		//axe//
	pointType->setModelsBump("fachwerkhaus2_2_LOD.fbx", "LOD_f_22.png", "LOD_f_22.png", "LOD_f_22.png"); //single house 1//
	pointType->setModelsBump("fachwerkhaus2_LOD.fbx", "LOD_f_2.png", "LOD_f_2.png", "LOD_f_2.png");//double house 1//
	pointType->setModelsBump("constuct_soldier.fbx", "marble.png", "marble.png", "marble.png");//green marble statue//
	pointType->setModelsBump("fachwerkhaus2_2_LOD.fbx", "LOD_f_22.png", "LOD_f_22.png", "LOD_f_22.png");//single house 2//
	pointType->setModelsBump("fachwerkhaus2_2_LOD.fbx", "LOD_f_22.png", "LOD_f_22.png", "LOD_f_22.png");//single house 3//
	pointType->setModelsBump("fachwerkhaus2_2_LOD.fbx", "LOD_f_22.png", "LOD_f_22.png", "LOD_f_22.png");//single house 4//
	pointType->setModelsBump("fachwerkhaus2_2_LOD.fbx", "LOD_f_23.png", "LOD_f_23.png", "LOD_f_23.png");//single house 5//
	pointType->setModelsBump("fachwerkhaus2_LOD.fbx", "LOD_f_2.png", "LOD_f_2.png", "LOD_f_2.png");//double house 2//
	pointType->setModelsBump("shield_deco3.fbx", "shield3.png", "shield3.png", "shield3.png");//position for shield 2//
	pointType->setModelsBump("fachwerkhaus2_3_LOD.fbx", "LOD_f_23.png", "LOD_f_23.png", "LOD_f_23.png");//single house type 2 number 1//
	pointType->setModelsBump("armorstand.fbx", "2h_axe.png", "2h_axeS.png", "2h_axeN.png");//Armorstand 1//
	pointType->setModelsBump("sword2.fbx", "sword2_C.png", "sword2_C.png", "sword2_C.png");//sword2  number 1//
	pointType->setModelsBump("sword4.fbx", "sword4_c.png", "sword4_c.png", "sword4_c.png");//sword4  number 1//
	pointType->setModelsBump("sword.fbx", "sword_C.png", "sword_C.png", "sword_C.png");//sword  number 1//
	pointType->setModelsBump("holzbank.fbx", "whitemarble.png", "whitemarble.png", "whitemarble.png");//bench  number 1//
	pointType->setModelsBump("plane.fbx", "pavement_color.png", "pavement_spec.png", "pavement_normal.png");


	//TRANSLATIONS FOR MODELS
	pointType->setTransformation(vec3(-8, 1, -6), vec3(-89.4, 0, 0), vec3(.002, .002, .002));//shield 1//
	pointType->setTransformation(vec3(-3.75, -1, -10), vec3(-89.52, 0, 0), vec3(.009, .009, .009));  //bridge//
	pointType->setTransformation(vec3(-15, 1, -6.5), vec3(-89.52, 0, 0), vec3(.008, .008, .008));//sign//
	pointType->setTransformation(vec3(-13, -1, -5.5), vec3(-89.52, 0, 0), vec3(.008, .008, .008));//wood canopy//
	pointType->setTransformation(vec3(-10.25, -0.75, -6), vec3(-89.5, 0, 0), vec3(0.002, 0.002, 0.002)); //position for the ax//
	pointType->setTransformation(vec3(-1.5, -1, -10), vec3(-89.5, 0, 0), vec3(0.01, 0.01, 0.01));//position for house 1//
	pointType->setTransformation(vec3(-15, -1, -10), vec3(-89.5, 0, 0), vec3(0.01, 0.01, 0.01));//postion for double house 1//
	pointType->setTransformation(vec3(-10.5, 2, -10), vec3(-89.52, 0, 0), vec3(0.01, 0.01, 0.01));//position for green marble statue//
	pointType->setTransformation(vec3(-17.75, -1, -10), vec3(-89.5, 0, 0), vec3(0.01, 0.01, 0.01));//position for house 2//
	pointType->setTransformation(vec3(-12.25, -1, -10), vec3(-89.5, 0, 0), vec3(0.01, 0.01, 0.01));//position for house 3//
	pointType->setTransformation(vec3(-6, -1, -10), vec3(-89.5, 0, 0), vec3(0.01, 0.01, 0.01));//posiotion for house 4//
	pointType->setTransformation(vec3(-19.5, -1, -10), vec3(-89.5, 0, 0), vec3(0.01, 0.01, 0.01));//posiotion for house 5//
	pointType->setTransformation(vec3(-22.5, -1, -7), vec3(-89.52, 0, 89.5), vec3(0.01, 0.01, 0.01));//postion for double house 2//
	pointType->setTransformation(vec3(-16, -0.8, -9), vec3(-89.52, 0, 0), vec3(0.009, 0.009, 0.009));//position for Shield 2//
	pointType->setTransformation(vec3(-15, -1, -5.5), vec3(-89.52, 0, 89.5), vec3(0.01, 0.01, 0.01));//position for single house type 2 number 1//
	pointType->setTransformation(vec3(-10, -1, -6), vec3(-89.52, 0, 0), vec3(0.004, 0.004, 0.004));//position for Armorstand number 1//
	pointType->setTransformation(vec3(-9.8, -0.75, -6), vec3(-89.52, 0, 0), vec3(0.0005, 0.0005, 0.0005));//position for sword2 number 1//
	pointType->setTransformation(vec3(-9.85, -0.75, -6), vec3(-89.52, 0, 0), vec3(0.002, 0.002, 0.002));//position for sword4 number 1//
	pointType->setTransformation(vec3(-9.7, -0.75, -6), vec3(-89.52, 0, 89.5), vec3(0.001, 0.001, 0.001));//position for sword number 1//
	pointType->setTransformation(vec3(-11.5, -1.25, -8.5), vec3(-89.52, 0, 0), vec3(0.009, 0.009, 0.009));//position for bench number 1//
	pointType->setTransformation(vec3(-10, -1.5, 0), vec3(-89.5, 0, 0), vec3(1, .8, 1));
	pointType->loadModels(point);

	//primitiveType* parralaxType = new primitiveType();
	////parralaxType->setModelsParrallax("armoredrecon.fbx", "armoredrecon_diff.png", "armoredrecon_spec.png", "armoredrecon_N.png", "armoredrecon_Height.png");
	////parralaxType->setTransformation(vec3(0, 0, 2), vec3(0, 0, 0), vec3(1, 1, 1));
	//parralaxType->loadModels(parralax);

	////Add to the displaylist in order for models etc to be loaded/rendered
	displayList.insert(displayList.end(), pointType->displayList.begin(), pointType->displayList.end());
	displayList.insert(displayList.end(), type->displayList.begin(), type->displayList.end());
	//displayList.insert(displayList.end(), parralaxType->displayList.begin(), parralaxType->displayList.end());
}

//Iterates through each component in displayList
//then the method is called repeatly to update gameobjects
void SplashScreen::Update(SDL_Event event)
{
	skyBoxObject->update();

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->update();
	}
}

//Used to bind the postprocessing, and clear the screen and the colour buffer
//to get the screen ready, then renders the Skybox and other GameObjects
//then adds renders the postprocessing effects.
void SplashScreen::render(SDL_Window *window)
{
	postProcessor.bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSkyBox();

	//alternative sytanx
	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		renderGameObject((*iter));
	}

	postProcessor.preDraw();
	GLint colourFilterLocation = postProcessor.getUniformVariableLocation("colourFilter");
	glUniformMatrix3fv(colourFilterLocation, 1, GL_FALSE, glm::value_ptr(selectedColour));
	//draw
	postProcessor.draw();

	//post draw
	postProcessor.postDraw();

	SDL_GL_SwapWindow(window);
}

//Renders each object in pObject, then proceeds to get the transform mesh and material for that object
//then binds the mesh/material for said object and proceeds to assign locations for each uniform location
//which will be needed for the shader files. We then get the Camera and light GameObject so we can access
//data for said objects to assign values to variables which will be passed into the shader to calculate
//other related stuff. From here it'll then draw the mesh and render each game object.
void SplashScreen::renderGameObject(GameObject * pObject)
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

		GLint lightPositionLocation = currentMaterial->getUniformLocation("lightPosition");

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
		vec4 ambientLightColour = light->getAmbientColour();
		vec3 lightDirection = light->getDirection();

		vec3 cameraPosition = mainCamera->getTransform()->getPosition();
		vec3 lightPosition = mainLight->getTransform()->getPosition();

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

		glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));

		glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);

		currentMaterial->unbind();
	}

	for (int i = 0; i < pObject->getChildCount(); i++)
	{
		renderGameObject(pObject->getChild(i));
	}
}

//Gets the mainCamera Object and assigns to variable.
//Checks for keyinput and calls appropriate camera method
//with appropriate enum type for movement which will then
//proceed to update the cameras position on screen.
//You can also rotate all objects on the screen 
//Mouse motion calls the camera's mouse method to deal with rotating the camera
void SplashScreen::UpdateInput(SDL_Event event){
	//While we still have events in the queue
	Camera * c = new Camera();
	c = mainCamera->getCamera();

	switch (event.type){

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym){

		case SDLK_w:
			c->movement(FORWARD);
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
		case SDLK_k:
			for (int i = 0; i < displayList.size(); i++){
				//determine which ones are models (have the name "a")
				if (displayList[i]->getName() == "a"){
					vec3 rotation = displayList[i]->getTransform()->getRotation();
					rotation.y += -1;

					displayList[i]->getTransform()->setRotation(rotation.x, rotation.y, rotation.z);
				}
			}

			break;
		case SDLK_i:
			switchNumber += 1;

			if (switchNumber > 3){
				switchNumber = 0;
			}

			FilterChanger();
			break;

		}//end key switch
	case SDL_MOUSEMOTION:
		int mouseX = event.motion.x;
		int mouseY = event.motion.y;
		glm::vec2 mousePos = glm::vec2(mouseX, mouseY);
		c->mouseUpdate(mousePos);
		break;
	}
}

//Calls the Skybox render function to render the skybox which is set up to render the skybox in a specific way
//then gets uniforms so that it knows what variables it's accessing the appropriate shader file.
//then passes values to the shader for it to calculate texture coordinates and such then proceeds
//to draw the cube mesh to screen.
void SplashScreen::renderSkyBox()
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
			glUniform4fv(cameraLocation, 1, glm::value_ptr(cam->getPosition()));
			glUniform1i(cubeTextureLocation, 0);

			glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);

			currentMaterial->unbind();
		}
		//CheckForErrors();
		GLenum error;
		do{
			error = glGetError();
		} while (error != GL_NO_ERROR);
	}

//Sets up the appropriate vertice positions for the cube, selects the appropriate indices to form the cube,
//then intiailizes the mesh so we can copy the mesh related data(indices/triangledata) to the mesh so we are ready
//for setting the material. We set up the position, intialize the material and load in the cube texture then set
//the material/mesh and transform then check to make sure no errors occur.
void SplashScreen::createSkyBox()
{
	Vertex triangleData[] = {
			{ vec3(-50.0f, 50.0f, 50.0f) },// Top Left
			{ vec3(-50.0f, -50.0f, 50.0f) },// Bottom Left
			{ vec3(50.0f, -50.0f, 50.0f) }, //Bottom Right
			{ vec3(50.0f, 50.0f, 50.0f) },// Top Right

			{ vec3(-50.0f, 50.0f, -50.0f) },// Top Left
			{ vec3(-50.0f, -50.0f, -50.0f) },// Bottom Left
			{ vec3(50.0, -50.0f, -50.0f) }, //Bottom Right
			{ vec3(50.0f, 50.0f, -50.0f) }// Top Right
	};

	GLuint indices[] = {
		//front
		0, 1, 2,
		3, 2, 0,

		//left
		3, 2, 6,
		6, 7, 3,

		//right
		7, 6, 5,
		5, 4, 7,

		//bottom
		4, 5, 1,
		1, 0, 4,

		//top
		4, 0, 3,
		3, 7, 4,

		//back
		1, 5, 6,
		6, 2, 1
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

	std::string posZTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysFront2048.png";
	std::string negZTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysBack2048.png";
	std::string posXTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysLeft2048.png";
	std::string negXTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysRight2048.png";
	std::string posYTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysUp2048.png";
	std::string negYTexturename = ASSET_PATH + TEXTURE_PATH + "CloudyLightRaysDown2048.png";

	material->loadCubeTexture(posZTexturename, negZTexturename, posXTexturename, negXTexturename, posYTexturename, negYTexturename);
	//create gameobject but don't add to queue!
	skyBoxObject = new GameObject();
	skyBoxObject->setMaterial(material);
	skyBoxObject->setTransform(t);
	skyBoxObject->setMesh(pMesh);

	GLenum error;
	do{
		error = glGetError();
	} while (error != GL_NO_ERROR);
}

//Cleans up the screen by destroying all objects rendered on the screen
//clears all gameobjects in displayList, and destroys the postprocessing
void  SplashScreen::cleanUp(){

	if (skyBoxObject)
	{
		skyBoxObject->destroy();
		delete skyBoxObject;
		skyBoxObject = NULL;
	}

	auto iter = displayList.begin();
	while (iter != displayList.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete (*iter);
			(*iter) = NULL;
			iter = displayList.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	displayList.clear();
	postProcessor.destroy();
}


//switch int enum which is based on user input, changes the type 
//of postprocessing active on the screen
void SplashScreen::FilterChanger(){
	
	switch (switchNumber){

	case 0:
		selectedColour = mat3(1);
		break;
	case 1:
		selectedColour = SEPIA_FILTER;
		break;
	case 2:
		selectedColour = BLACK_AND_WHITE_FILTER;
		break;
	case 3:
		selectedColour = GREEN_SCALE_FILTER;
		break;
	}
}


