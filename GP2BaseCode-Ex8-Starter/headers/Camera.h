//
//  Camera.h
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Camera_h
#define Camera_h


#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"

enum MovementType { FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT };

class Camera:public Component
{
public:
    Camera();
    ~Camera();
    
	void update();
    
	void setLook(float x, float y, float z);
    
	void setUp(float x, float y, float z);
    
    void setNearClip(float near);
    void setFarClip(float far);
	void setFOV(float FOV);
    
	void setAspectRatio(float ratio);
    
	mat4& getView();
	mat4& getProjection();

	void translate(glm::vec3& direction);
	void applyMovement(MovementType movement);
	





protected:
private:
	glm::vec3 m_position;
	glm::vec3 m_direction;


	vec3 m_LookAt;
	vec3 m_Up;
    
	mat4 m_View;
	mat4 m_Projection;
    
	float m_NearClip;
	float m_FarClip;
	float m_FOV;
	float m_AspectRatio;
};

#endif
