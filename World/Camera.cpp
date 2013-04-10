
#define GLM_SWIZZLE

#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include <sstream>


Camera::Camera()
{
	reset();
}



// Reset the camera back to its defaults
void Camera::reset()
{
	setPosition(glm::vec3(0.0, 0.0, 0.5));
	lookAt(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));

	fieldOfView   = 45.0f; // frustrum viewing apeture
	aspectRatio   = 4.0f/3.0f;
	nearFieldClip = 0.1;   // clip anything closer than this
	farFieldClip  = 200; // clip anything farther than this
	projection    = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



// Set the camera to an arbitrary location without changing orientation
void Camera::setPosition(const glm::vec3& pos)
{
	position = pos;
}



// Set the orientation of the camera without changing its position
void Camera::lookAt(const glm::vec3& newLookVector, const glm::vec3& newUpVector)
{
	lookDirection = newLookVector;
	upVector = newUpVector;
}



void Camera::moveX(float units)
{
	float abs_units = (float)fabs(units);
	glm::vec3 direction = glm::normalize(glm::cross(lookDirection, upVector));
	glm::vec3 shiftvector = abs_units * (units < 0.0f ? -direction : direction);
	position += shiftvector;
	lookDirection = glm::normalize(lookDirection + shiftvector);
}



void Camera::moveY(float units)
{
	float abs_units = (float)fabs(units);
	glm::vec3 shiftvector = abs_units * (units < 0.0f ? -upVector : upVector);
	position += shiftvector;
	lookDirection = glm::normalize(lookDirection + shiftvector);
}



void Camera::moveZ(float units)
{
	float abs_units = (float)fabs(units);
	glm::vec3 shiftvector = abs_units * (units < 0.0f ? -lookDirection : lookDirection);
	position += shiftvector;
	lookDirection = glm::normalize(lookDirection + shiftvector);
}



// Translate the camera along X/Y/Z
void Camera::translate(const glm::vec3& xyzTheta)
{
	glm::vec4 pos(position, 1.0);
	glm::vec4 look(lookDirection, 1.0);
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), xyzTheta);
	pos = matrix * pos;
	look = matrix * look;

	position = pos.xyz();
	lookDirection = look.xyz();
}



// Pitch the camera along the axis orthogonal to the up and look vectors
void Camera::pitch(float theta)
{
	glm::vec4 look(lookDirection, 0.0);
	glm::vec4 up(upVector, 0.0);

	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), -position); // Move to the origin
	matrix = glm::rotate(matrix, theta, glm::cross(lookDirection, upVector)); // Pitch the camera
	matrix = glm::translate(matrix, position); // Move it back to it's original spot

	look = matrix * look;
	up = matrix * up;

	lookDirection = look.xyz();
	upVector = up.xyz();
}



// Yaw the camera along the up vector
void Camera::yaw(float theta)
{
	glm::vec4 look(lookDirection, 0.0);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), theta, upVector);
	look = matrix * look;
	lookDirection = look.xyz();
}



// Roll the camera along the look axis
void Camera::roll(float theta)
{
	glm::vec4 up(upVector, 0.0);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), theta, lookDirection);
	up = matrix * up;
	upVector = up.xyz();
}



// Sets the perspective of the camera
void Camera::setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearclipdistance, float farclipdistance)
{
	fieldOfView   = fieldOfViewDegrees;
	aspectRatio   = aspectRatio;
	nearFieldClip = nearclipdistance;
	farFieldClip  = farclipdistance;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setFieldOfView(float degrees)
{
	fieldOfView = degrees;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setAspectRatio(float ratio)
{
	aspectRatio = ratio;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setNearFieldClipDistance(float distance)
{
	nearFieldClip = distance;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setFarFieldClipDistance(float distance)
{
	farFieldClip = distance;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



//accessors:

glm::vec3 Camera::getLookDirection()
{
	return lookDirection;
}



glm::vec3 Camera::getPosition()
{
	return position;
}



glm::vec3 Camera::getUpVector()
{
	return upVector;
}



float Camera::getFOV()
{
	return fieldOfView;
}



float Camera::getAspectRatio()
{
	return aspectRatio;
}



float Camera::getNearFieldClip()
{
	return nearFieldClip;
}



float Camera::getFarFieldClip()
{
	return farFieldClip;
}



glm::mat4 Camera::getProjectionMatrix()
{
	return projection;
}



std::string Camera::toString()
{
	std::stringstream ss;

	ss << "LookV: <" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "> ";
	ss << "UpV: <"   << upVector.x << ", " << upVector.y << ", " << upVector.z << "> ";
	ss << "Pos: <"   << position.x << ", " << position.y << ", " << position.z << ">";

	return ss.str();
}


/*
void Camera::pitchAndRoll(int x, int y)
{
	static int doneOnce = 0, cam_x, cam_y;

	glm::vec3 axis_y(0.0, 1.0, 0.0);
	glm::vec3 axis_x(1.0,0.0,0.0);

	float angleX = 0.0f;
	float angleY = 0.0f;
	if(doneOnce)
		angleX = (cam_x - x)/5.0f;
	cam_x = x;
	if(doneOnce)
		angleY = (cam_y - y)/5.0f;
	cam_y = y;

	model = glm::rotate(model, angleX, axis_y);

	model = glm::rotate(model, angleY, axis_x);

	doneOnce = 1;
}
*/
