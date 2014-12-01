#include "primitiveType.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Vertex.h"


Vertex triangleVertices[] = 
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


primitiveType::primitiveType()
{


}

primitiveType::~primitiveType(){

}


void primitiveType::render()
{


}

void setUpPrimitive(std::string name, vec3 pos){

	//this method should setup any primitive we want

	float x, y, z;
	x = pos.x;
	y = pos.y;
	z = pos.z;

	GameObject * cube = new GameObject();
	cube->setName("Cube");
	Transform *transform = new Transform();
	transform->setPosition(x,y,z);
	cube->setTransform(transform);

	Material * material = new Material();
	//std::string vsPath = ASSET_PATH + SHADER_PATH + "/specularVS.glsl";
	//std::string fsPath = ASSET_PATH + SHADER_PATH + "/specularFS.glsl";
	//material->loadShader(vsPath, fsPath);
	cube->setMaterial(material);

	Mesh * mesh = new Mesh();
	cube->setMesh(mesh);

}



void primitiveType::cube()
{
	//may move this outside of method
	GLuint indices[] = {
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

	//our indices for cube.

}

