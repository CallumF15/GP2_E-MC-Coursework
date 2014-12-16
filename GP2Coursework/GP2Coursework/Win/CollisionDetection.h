#ifndef CollisionDetection_h
#define CollisionDetection_h


#include "GameObject.h"
#include <vector>

class CollisionDetection{

public:

	void getAllObjects(std::vector<GameObject*> objectArray);

protected:

private:
	std::vector<GameObject*>  mainList;

};

#endif