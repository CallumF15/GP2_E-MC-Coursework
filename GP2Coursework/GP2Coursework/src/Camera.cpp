

///This class was originally made by Brian Mcdonald
///but alterations were made by Callum Flannagan ///

#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"


//Constructor. Assign values to header variables.
Camera::Camera()
{
	
	m_Type = "Camera";

	m_position = vec3(0, 1, 10);
	m_direction = vec3(0.0, 0.0, -1.0f);

	m_LookAt = vec3(0.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
	m_FOV = 45.0f;
	m_AspectRatio = 16.0f / 9.0f;
	m_View = mat4();
	m_Projection = mat4();
}

//Destructor.
Camera::~Camera()
{

}

//Update method. Called to constantly update the position of the camera based off the calculations off other methods.
void Camera::update()
{
	//need to sort out why this "getTransform()" doesn't get the proper position value
	m_Parent->getTransform()->setPosition(m_position.x, m_position.y, m_position.z);
	m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_View = glm::lookAt(m_position, m_position + m_direction, m_Up);
}

//Calculates the rotation in 3D space with the mouse.
void Camera::mouseUpdate(const glm::vec2& newMousePos)
{
	glm::vec2 mouseDelta = newMousePos - oldMousePos;

	if (glm::length(mouseDelta) > 50.0f){
		oldMousePos = newMousePos;
		return;
	}


	const float ROTATIONAL_SPEED = 0.01f;
	
	strafedirection = glm::cross(m_direction, m_Up);
	glm::mat4 rotator = glm::rotate(mat4(1.0f), -mouseDelta.x * ROTATIONAL_SPEED, m_Up) *
		glm::rotate(mat4(1.0f), -mouseDelta.y * ROTATIONAL_SPEED, strafedirection);

	m_direction = glm::mat3(rotator) * m_direction;

	oldMousePos = newMousePos;
}

//Passed in variable determines which sort of movement occurs and
//calls the appropriate enum of type MovementType and either calculates
//or calls appropriate method
void Camera::movement(MovementType movementType)
{
	switch (movementType){

	case  FORWARD:
		m_position += movementSpeed * m_direction;
		break;
	case BACKWARD:
		m_position += -movementSpeed * m_direction;
		break;
	case STRAFE_LEFT:
		strafeLeft();
		break;
	case STRAFE_RIGHT:
		strafeRight();
		break;
	case UP:
		m_position += movementSpeed * m_Up;
		break;
	case DOWN:
		m_position -= movementSpeed * m_Up;
		break;
	case RESET:
		m_position = vec3(0, 0, 0);
		m_direction = vec3(0.0, 0.0, -1.0f);
		break;
	}
}

//Calculates movement to the left
void Camera::strafeLeft(){
	m_position -= movementSpeed * strafedirection;
}

//Calculates movement to the Right
void Camera::strafeRight()
{
	m_position += movementSpeed * strafedirection;
}


//Returns the position of the casmera
vec3 Camera::getPosition(){
	return m_position;
}

//End Methods









//Below are just setters/getters which assign and return values
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