#ifndef primitiveType_h
#define primitiveType_h


#include <GL/glew.h>
//#include "Vertex.h"


//#include <glm/glm.hpp>
//using glm::vec3;

#include "Component.h"

static class primitiveType : public Component{


public:

	primitiveType();
	~primitiveType();

	void render(); //needed to render primitive to screen.

	static void cube();





private:

	//Vertex triangleVertices;

	//Vertex cubeIndices;


};



#endif