#ifndef primitiveType_h
#define primitiveType_h


//#include <GL/glew.h>

#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "FBXLoader.h"


#include "Vertex.h"
#include <vector>
#include <glm/glm.hpp>
using glm::vec3;

#include <string>

#include "Material.h"

enum primitiveShape 
{ 
	cube, 
	triangle
};

enum shaderType{
	bump,
	parralax
};

class primitiveType{

public:
	primitiveType();
	~primitiveType();

	void createPrimitive(primitiveShape shape, vec3 position, vec3 rotation, vec3 scaling);
	void setPrimitiveTexture(std::string diffTexturePath, std::string specTexturePath, std::string bumpTexturePath);

	void CreatePrim(std::string diffTexturePath, std::string specTexturePath, std::string bumpTexturePath,
		primitiveShape shape, vec3 position, vec3 rotation, vec3 scaling);

	void setModelsBump(std::string modelPath, std::string diffusePath, 
		std::string specularPath, std::string bumpMapPath);

	void setModelsParrallax(std::string modelPath, std::string diffusePath,
		std::string specularPath, std::string bumpMapPath, std::string heightMapPath);

	void setTransformation(vec3 position, vec3 rotation, vec3 scaling);
	void loadModels(shaderType type);

	void determineShader(shaderType type);

	std::vector<GameObject*> displayList;
	std::vector<GameObject*> getDisplayList();
	void setDisplaylist(std::vector<GameObject*> List);

	//May delete this
	GLuint getIndices();
	void setIndices(GLuint indices[]);

private:
	 void CheckShape(primitiveShape shape);

	 primitiveShape shape;
	 std::vector<std::string> fileArray;
	 std::vector<std::string> diffuseArray;
	 std::vector<std::string> specularArray;

	 //for bump mapping
	 std::vector<std::string> bumpArray;
	 //for parrallax mapping
	 std::vector<std::string> heightArray;

	 std::vector<vec3> m_position;
	 std::vector<vec3> m_rotation;
	 std::vector<vec3> m_scaling;
	
	 std::string shaderFilenameVS, shaderFilenameFS;
	 std::string heightTexturePath;

	 Mesh* mesh;
	 Material* materialPrimitive;

	 GLuint texture;
};



#endif