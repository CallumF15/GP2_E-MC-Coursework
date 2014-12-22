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

SplashScreen::SplashScreen()
{

}

SplashScreen::~SplashScreen(){

}

void SplashScreen::LoadContent(){
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
	t->setPosition(46.0f, 32.0f, -47.0f);
	mainLight->setTransform(t);

	Light * light = new Light();
	mainLight->setLight(light);
	displayList.push_back(mainLight);

	//Model loading
	type->setModelsBump("armoredrecon.fbx", "armoredrecon_diff.png", "armoredrecon_spec.png", "armoredrecon_N.png");
	type->setTransformation(vec3(-5, 0, -10), vec3(0, 0, 0), vec3(1, 1, 1));
	type->loadModels(bump);


	primitiveType* pointType = new primitiveType();

	//include file for models
	pointType->setModelsBump("sword4.fbx", "sword2_C.png", "sword_S.png", "sword_N.png");
	pointType->setModelsBump("2h_axe.fbx", "2h_axe.png", "2h_axeS.png", "2h_axeN.png");
	pointType->setModelsBump("knife2.fbx", "kn5_COL.png", "kn5_SPEC.png", "kn5_NRM.png");
	pointType->setModelsBump("shield_deco3.fbx", "shield_C.png", "shield_D.png", "shield_N.png");
	pointType->setModelsBump("constuct_bridge.fbx", "s_12.png", "s_12S.png", "s_12N.png");
	pointType->setModelsBump("constuct_shild_A.fbx", "p_1.png", "p_1S.png", "s_12N.png");
	pointType->setModelsBump("constuct_understand_wood.fbx", "u_8.png", "u_8S.png", "u_8N.png");
	pointType->setModelsBump("planet_earth.fbx", "mat_plan2.png", "mat_plan2.png", "mat_plan2.png");
	pointType->setModelsBump("Tank1.fbx", "Tank1DF.png", "Tank1_S.png", "Tank1_H.png" );
	pointType->setModelsBump("barrel.fbx", "barrel_color_01.png", "barrel_spec_01.png", "barrel_nmap_01png");
	//set transformations for models
	pointType->setTransformation(vec3(-1, 1, -10), vec3(-89.4, 0, 0), vec3(.01, .01, .01));
	pointType->setTransformation(vec3(-10, 1, -10), vec3(-89.4, 0, 0), vec3(0.01, .01, .01));
	pointType->setTransformation(vec3(-1, 1, -10), vec3(-89.4, 0, 0), vec3(0.01, 0.01, 0.01));
	pointType->setTransformation(vec3(-8, 1, -10), vec3(-89.4, 0, 0), vec3(.02, .02, .02));
	pointType->setTransformation(vec3(-8, 1, 0), vec3(-90, 0, 0), vec3(.02, .02, .02));  //bridge
	pointType->setTransformation(vec3(-8, 1, -5), vec3(0, 0, 0), vec3(.04, .04, .04));
	pointType->setTransformation(vec3(-10, 1, -5), vec3(-89.4, 0, 0), vec3(.02, .04, .02));
	pointType->setTransformation(vec3(-46, 32, -40), vec3(-90, 0, 90), vec3(0.2, 0.2, 0.2));
	pointType->setTransformation(vec3(-13, 1, 0), vec3(180, 90, 180), vec3(0.5, 0.5, 0.5));  //tank
	pointType->setTransformation(vec3(-15, 1, 0), vec3(180, 90, 180), vec3(0.02, 0.02, 0.02));  //barrel
	//plane related

	pointType->loadModels(point);


	//primitiveType* parralaxType = new primitiveType();
	//parralaxType->setModelsBump("plane.fbx", "pavement_color.png", "pavement_spec.png", "pavement_normal.png");
	//parralaxType->setTransformation(vec3(-10, 1, -5), vec3(-90, 0, 0), vec3(.02, .04, .02));
	////parralaxType->setModelsParrallax("armoredrecon.fbx", "armoredrecon_diff.png", "armoredrecon_spec.png", "armoredrecon_N.png", "armoredrecon_Height.png");
	////parralaxType->setTransformation(vec3(0, 0, 2), vec3(0, 0, 0), vec3(1, 1, 1));
	//parralaxType->loadModels(parralax);

	primitiveType* primimtiveShapes = new primitiveType();
	primimtiveShapes->setModelsBump("plane.fbx", "pavement_color.png", "pavement_spec.png", "pavement_normal.png");
	primimtiveShapes->setModelsBump("plane.fbx", "pavement_color.png", "pavement_spec.png", "pavement_normal.png");
	primimtiveShapes->setTransformation(vec3(-10, 1, 0), vec3(-89.5, 0, 0), vec3(.2, .2, 1));
	primimtiveShapes->setTransformation(vec3(-10, 1, 0), vec3(-90, 0, 0), vec3(.1, .1, 1));
	primimtiveShapes->loadModels(point);

	////Add to the displaylist in order for models etc to be loaded/rendered
	displayList.insert(displayList.end(), pointType->displayList.begin(), pointType->displayList.end());
	displayList.insert(displayList.end(), primimtiveShapes->displayList.begin(), primimtiveShapes->displayList.end());
	displayList.insert(displayList.end(), type->displayList.begin(), type->displayList.end());
	//displayList.insert(displayList.end(), parralaxType->displayList.begin(), parralaxType->displayList.end());
}

void SplashScreen::Update(SDL_Event event)
{
	skyBoxObject->update();

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->update();
	}
}

void SplashScreen::render(SDL_Window *window)
{
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

	SDL_GL_SwapWindow(window);
}

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
		}//end key switch
	case SDL_MOUSEMOTION:
		int mouseX = event.motion.x;
		int mouseY = event.motion.y;
		glm::vec2 mousePos = glm::vec2(mouseX, mouseY);
		c->mouseUpdate(mousePos);
		break;
	}
}

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

	//CheckForErrors();
	GLenum error;
	do{
		error = glGetError();
	} while (error != GL_NO_ERROR);
}

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
}
