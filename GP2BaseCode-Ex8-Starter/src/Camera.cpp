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

#ifndef M_PI
#define M_PI 3.1415926525
#endif

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
	//vec3 position = m_Parent->getTransform()->getPosition();
	position = m_Parent->getTransform()->getPosition();
	m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_View = glm::lookAt(position, lookvec, m_Up);

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
		m_position += direction *m_deltatime *  speed;
		break;
	case BACKWARD:
		m_position -= direction * m_deltatime * speed;
		break;
	case STRAFE_LEFT:
		m_position -= right * m_deltatime * speed;
		break;
	case STRAFE_RIGHT:
		m_position += right * m_deltatime * speed;
		break;
	}
	
}
void Camera::calculateMovement()
{
	horizontalAngle += mouseSpeed  * float(640 / 2 - m_MouseX);
	verticalAngle += mouseSpeed  * float(480 / 2 - m_MouseY);

	 direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);

	// up = glm::cross(right, direction);

}

void Camera::lockCamera()
{
	if (camPitch > 90)
		camPitch = 90;
	if (camPitch < -90)
		camPitch = -90;
	if (camYaw < 0.0)
		camYaw += 360;
	if (camYaw > 360)
		camYaw -= 360;
}

void Camera::moveCamera(float distance, float direction){

	float radian = (camYaw + direction)* M_PI / 180.0;
	camX -= glm::sin(radian)*distance;
	camZ -= glm::cos(radian)*distance;
}

void Camera::moveCameraUp(float distance, float direction){

	float radian = (camPitch + direction)* M_PI / 180.0;
	camY += glm::sin(radian)*distance;
}

void Camera::control(SDL_Window* window, float moveVelocity, float mouseVelocity, bool mi){
	if (mi){
		int midX = 320;
		int midY = 240;
		
		int tmpx, tmpy;
		tmpx = m_MouseX;
		tmpy = m_MouseY;
		camYaw += mouseVelocity * (midX - tmpx);
		camPitch += mouseVelocity * (midY - tmpy);
		lockCamera();

		SDL_WarpMouseInWindow(window, midX, midY);
		movement(mouseVelocity, moveVelocity);
	}
}

void Camera::movement(float mouseVelocity, float moveVelocity)
{
	SDL_Event events;

	while (SDL_PollEvent(&events)) {
		switch (events.type){

		case SDL_KEYDOWN:
			switch (events.key.keysym.sym){

			case SDLK_w:
				if (camPitch != 90 && camPitch != -90){
					moveCamera(moveVelocity, 0.0);
					moveCameraUp(moveVelocity, 0.0);
				}
				break;
			case SDLK_s:
				if (camPitch != 90 && camPitch != -90){
					moveCamera(moveVelocity, 180.0);
					moveCameraUp(moveVelocity, 180.0);
				}
				break;
			case SDLK_a:
				moveCamera(moveVelocity, 90.0);
				break;
			case SDLK_d:
				moveCamera(moveVelocity, 270.0);
				break;

			case SDL_MOUSEMOTION:

				mouseIn = true;
				SDL_ShowCursor(SDL_DISABLE);

				int mouseX = events.motion.x;
				int mouseY = events.motion.y;

				setMousePosition(mouseX, mouseY);


				break;
			}
		}

		//direction = vec3(
		//	cos(camPitch) * sin(camYaw),
		//	sin(verticalAngle),
		//	cos(camPitch) * cos(camYaw)
		//	);

		int lookz = m_position.x + (int)(30 * glm::cos(camYaw));
		int lookx = m_position.y + (int)(30 * glm::sin(camYaw));
		int looky = m_position.y + (int)(30 * glm::tan(camPitch));
		lookvec = vec3(lookx, looky, lookz);
		
		//m_Parent->getTransform()->setRotation()
		glRotatef(-camPitch, 1.0, 0.0, 0.0);
		glRotatef(-camYaw, 0.0, 1.0, 0.0);
	}
}

void Camera::updateCamera(){
	glTranslatef(-camX, -camY, -camZ);
}






void Camera::setTime(float deltatime)
{
	m_deltatime = deltatime;
}

void Camera::setMousePosition(int mouseX, int mouseY)
{
	//Center the mouses position
	m_MouseX = mouseX;
	m_MouseY = mouseY;
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