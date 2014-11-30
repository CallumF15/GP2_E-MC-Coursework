//
//  Camera.c
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

//TODO LIST:
//1. get mouse position
//2. change code to make camera 3D

Camera::Camera()
{
	m_Type = "Camera";


	m_LookAt = vec3(0.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);

	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
	m_FOV = 45.0f;
	m_AspectRatio = 16.0f / 9.0f;
	m_View = mat4();
	m_Projection = mat4();


	m_direction = vec3(1.0, 0.0, 1.0f);
}

Camera::~Camera()
{
    
}

void Camera::update()
{
	//get the position from the transform
	vec3 position = m_Parent->getTransform()->getPosition();
    
	m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_View = glm::lookAt(position, m_position + m_direction, m_Up);

	//m_View = glm::lookAt(position, m_position + m_LookAt, m_Up);
}


//Methods

void Camera::translate(glm::vec3& direction)
{
	m_position += direction;
}

void Camera::applyMovement(MovementType movement)
{
	switch (movement)
	{
	case FORWARD:
		m_position += m_direction;
		break;
	case BACKWARD:
		m_position -= m_direction;
		break;
	case STRAFE_LEFT:

		m_position += glm::cross(m_direction, m_Up);
		break;
	case STRAFE_RIGHT:
		m_position -= glm::cross(m_direction, m_Up);
		break;
	}
}


//End Methods











void Camera::setLook(float x, float y, float z)
{
    m_LookAt = vec3(x, y, z);
}

void Camera::setUp(float x, float y, float z)
{
    m_Up = vec3(x, y, z);
}


 void Camera::setNearClip(float near)
 {
     m_NearClip = near;
 }
 
 void Camera::setFarClip(float far)
 {
     m_FarClip = far;
 }

void Camera::setFOV(float FOV)
{
    m_FOV = FOV;
}

void Camera::setAspectRatio(float ratio)
{
    m_AspectRatio = ratio;
}

mat4& Camera::getView()
{
    return m_View;
}

mat4& Camera::getProjection()
{
    return m_Projection;
}