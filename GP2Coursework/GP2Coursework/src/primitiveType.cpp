///////////////////////////////////////////////////
//This class was implemented by Callum Flannagan//
//////////////////////////////////////////////////

#include "primitiveType.h"


const std::string ASSET_PATH = "../assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
const std::string MODEL_PATH = "models/";

//vertice positions used to make shapes
Vertex triangleData[] =
{
	{ vec3(-0.5f, 0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 0.0f) },// Top Left
	{ vec3(-0.5f, -0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 1.0f) },// Bottom Left
	{ vec3(0.5f, -0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 1.0f) }, //Bottom Right
	{ vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 0.0f) },// Top Right


	//back
	{ vec3(-0.5f, 0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 0.0f) },// Top Left
	{ vec3(-0.5f, -0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 1.0f) },// Bottom Left
	{ vec3(0.5f, -0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 1.0f) }, //Bottom Right
	{ vec3(0.5f, 0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 0.0f), }// Top Right
};

//indices to form a plane
GLuint planeindices[] = {
	//front
	3, 0, 4,
	3, 8, 4
};

//indices to form a cube
GLuint cubeIndices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 1,

	//top
	5, 0, 7,
	5, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};

//constructor
primitiveType::primitiveType()
{

}

//destructor
primitiveType::~primitiveType(){

}



//Allow's you to create a shape at a given position
void primitiveType::createPrimitive(shaderType type, vec3 position, vec3 rotation, vec3 scaling)
{
	GameObject* objectShape = new GameObject(); //intialize classes
	Transform* transform = new Transform();
	Mesh *mesh = new Mesh();

	determineShader(type); //assigns the shaderfile name based on input
	
	std::string vsPath = ASSET_PATH + SHADER_PATH + shaderFilenameVS; //creates path directory to VS shader
	std::string fsPath = ASSET_PATH + SHADER_PATH + shaderFilenameFS; // creates path directory to FS shader
	materialPrimitive->loadShader(vsPath, fsPath);	//loads the VS & FS shader from file

	objectShape->setMaterial(materialPrimitive); //sets material for object
	objectShape->setMesh(mesh);	//sets mesh for object

	transform->setPosition(position.x, position.y, position.z); //sets position for object
	transform->setRotation(rotation.x, rotation.y, rotation.z); //sets rotation for object
	transform->setScale(scaling.x, scaling.y, scaling.z);	//sets scaling for object
	objectShape->setTransform(transform); //assigns transform for object
	displayList.push_back(objectShape); //adds object to vector object array


	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)	//iterates through each gameobject
	{
		(*iter)->init(); //intializes game object
		(*iter)->getMesh()->copyVertexData(8, sizeof(Vertex), (void**)triangleData); //copys vertex data (triangle data) for said object
		(*iter)->getMesh()->copyIndexData(36, sizeof(int), (void**)planeindices); //copies the index data (indices) for said object
	}
}

//Used to allocate the texture for the primitive shape
void primitiveType::setPrimitiveTexture(std::string diffTexturePath, std::string specTexturePath, std::string bumpTexturePath){

	diffuseArray.push_back(diffTexturePath); //adds texture to array
	specularArray.push_back(specTexturePath); //adds texture to array
	bumpArray.push_back(bumpTexturePath); //adds texture to array

	for (int i = 0; i < diffuseArray.size(); i++) {  //iterates through array 

		materialPrimitive = new Material(); //intializes object

		std::string diffTexturePath = ASSET_PATH + TEXTURE_PATH + diffuseArray[i];	//assigns file path directory
		std::string specTexturePath = ASSET_PATH + TEXTURE_PATH + specularArray[i]; //assigns file path directory
		std::string bumpTexturePath = ASSET_PATH + TEXTURE_PATH + bumpArray[i]; //assigns file path directory

		materialPrimitive->loadDiffuseMap(diffTexturePath);				//loads texture map for material
		materialPrimitive->loadSpecularMap(specTexturePath);			//loads texture map for material
		materialPrimitive->loadBumpMap(bumpTexturePath);			   //loads texture map for material
	}
}

//Sets the directories for bump mapping
void primitiveType::setModelsBump(std::string modelFilename, std::string diffTexturePath,
	std::string specTexturePath, std::string bumpTexturePath){

	fileArray.push_back(modelFilename);      //adds filename to array
	diffuseArray.push_back(diffTexturePath);	//adds texture path to array
	specularArray.push_back(specTexturePath);	//adds texture path to array
	bumpArray.push_back(bumpTexturePath);	//adds texture path to array
}

//Sets the directories for parrallax mapping
void primitiveType::setModelsParrallax(std::string modelFilename, std::string diffTexturePath,
	std::string specTexturePath, std::string bumpTexturePath, std::string heightMapPath){

	fileArray.push_back(modelFilename);   //adds filename to array
	diffuseArray.push_back(diffTexturePath); //adds texture path to array
	specularArray.push_back(specTexturePath); //adds texture path to array
	bumpArray.push_back(bumpTexturePath); //adds texture path to array
	heightArray.push_back(heightMapPath); //adds texture path to array
}

//Sets the transformations for models
void primitiveType::setTransformation(vec3 position, vec3 rotation, vec3 scaling){

	m_position.push_back(position); //adds to array for setting position for model
	m_rotation.push_back(rotation); //adds to array for setting rotation for model
	m_scaling.push_back(scaling); //adds to array for setting scaling for model
}

//loads the models
void primitiveType::loadModels(shaderType type){

	for (int i = 0; i < fileArray.size(); i++) { //iterates through array

		std::string modelPath = ASSET_PATH + MODEL_PATH + fileArray[i];			//gets current filename and creates path to model
		std::string diffTexturePath = ASSET_PATH + TEXTURE_PATH + diffuseArray[i];	//gets texture name and creates path directory
		std::string specTexturePath = ASSET_PATH + TEXTURE_PATH + specularArray[i]; //gets texture name and creates path directory
		std::string bumpTexturePath = ASSET_PATH + TEXTURE_PATH + bumpArray[i]; //gets texture name and creates path directory

		determineShader(type);  //assigns the shaderfile name based on input

		if (type == parralax) //if shader specified is parralax include this code
			heightTexturePath = ASSET_PATH + TEXTURE_PATH + heightArray[i]; //gets texture name and creates path directory

		GameObject * go = loadFBXFromFile(modelPath);  //load model from file and assign to variable

		for (int b = 0; b < go->getChildCount(); b++) //iterate through each child in gameobject
		{
			go->setName("a"); //set object name
			Material * material = new Material(); //intialize variable
			material->init(); //call material intialize method

			std::string vsPath = ASSET_PATH + SHADER_PATH + shaderFilenameVS; //create file directory path for shader
			std::string fsPath = ASSET_PATH + SHADER_PATH + shaderFilenameFS; //create file directory path for shader
			material->loadShader(vsPath, fsPath); //load shader 

			material->loadDiffuseMap(diffTexturePath); //load texture from file
			material->loadSpecularMap(specTexturePath); //load texture from file
			material->loadBumpMap(bumpTexturePath); //load texture from file

			if (type == parralax) //if shader specified is parralax include this code
				material->loadHeightMap(heightTexturePath); //load height map texture

			go->getChild(b)->setMaterial(material); //set material for said game object
		}

		go->getTransform()->setRotation(m_rotation[i].x, m_rotation[i].y, m_rotation[i].z);  //set rotation for model
		go->getTransform()->setScale(m_scaling[i].x, m_scaling[i].y, m_scaling[i].z); //set scale for model
		go->getTransform()->setPosition(m_position[i].x, m_position[i].y, m_position[i].z); //set position for model
		displayList.push_back(go); //add gameobject to vector array
	}
}

//Determines which shader to use (assigns shader filepath)
void primitiveType::determineShader(shaderType type){

	switch (type){	//based on enum type ShaderType it'll assign value to variable

	case parralax:
		shaderFilenameVS = "/ParallaxMappingVS.glsl";
		shaderFilenameFS = "/ParallaxMappingFS.glsl";
		break;
	case bump:
		shaderFilenameVS = "/BumpmappingVS.glsl";
		shaderFilenameFS = "/BumpmappingFS.glsl";
		break;
	case directionalLight:
		shaderFilenameVS = "/DirectionalLightTextureVS.glsl";
		shaderFilenameFS = "/DirectionalLightTextureFS.glsl";
		break;
	case texturing:
		shaderFilenameVS = "/textureVS.glsl";
		shaderFilenameFS = "/textureFS.glsl";
		break;
	case point:
		shaderFilenameVS = "/pointLightVS.glsl";
		shaderFilenameFS = "/pointLightFS.glsl";
		break;
	default:
		break;
	}
}


std::vector<GameObject*> primitiveType::getDisplayList(){
	return displayList; //returns displayList
}

void primitiveType::setDisplaylist(std::vector<GameObject*> List){
	for (int i = 0; i < List.size(); i++){
		displayList.push_back(List[i]); //sets disyList for each object in List
	}
}
///This class was made my Callum Flannagan
