#ifndef primitiveType_h
#define primitiveType_h


//#include <GL/glew.h>

#include "Vertex.h"
#include <glm/glm.hpp>
using glm::vec3;


#include <string>

#include "Component.h"


enum primitiveShape 
{ 
	cube, 
	triangle
};

class primitiveType : public Component{

public:

	primitiveType();
	~primitiveType();

	void render(); //needed to render primitive to screen.
	void setUpPrimitive(primitiveShape shape, std::string name, vec3 pos, GameObject* objectShape, Transform* transform, Material* material, Mesh* mesh);

	std::vector<GameObject*> displayList;

private:
	 primitiveShape CheckShape(primitiveShape shape);

};



#endif