
#define GLM_SWIZZLE

#include "Camera.hpp"
#include "Scene.hpp"
#include <memory>
#include <iostream>


Camera::Camera(const std::shared_ptr<Scene>& scene)
	: scene(scene)
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
	farFieldClip  = 50.0; // clip anything farther than this
	projection    = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setScene(const std::shared_ptr<Scene>& newScene)
{
	scene = newScene;
}



// Set the camera to an arbitrary location without changing orientation
void Camera::setPosition(glm::vec3 pos)
{
	position = glm::normalize(pos);
}



// Set the orientation of the camera without changing its position
void Camera::lookAt(glm::vec3 look, glm::vec3 up)
{
	lookDirection = glm::normalize(look);
	upVector = glm::normalize(up);
}



void Camera::moveX(float units)
{
	float abs_units = (float)fabs(units);
	glm::vec3 direction = glm::normalize(glm::cross(lookDirection, upVector));
	glm::vec3 shiftvector = abs_units * (units<0.0? -direction: direction);
	position += shiftvector;
	lookDirection = glm::normalize(lookDirection + shiftvector);

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
}



void Camera::moveY(float units)
{
	float abs_units = (float)fabs(units);
	glm::vec3 shiftvector = abs_units * (units<0.0? -upVector: upVector);
	position += shiftvector;
	lookDirection = glm::normalize(lookDirection + shiftvector);

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
}



void Camera::moveZ(float units)
{
	float abs_units = (float)fabs(units);
	glm::vec3 shiftvector = abs_units * (units<0.0? -lookDirection: lookDirection);
	position += shiftvector;
	lookDirection = glm::normalize(lookDirection + shiftvector);

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
}



// Translate the camera along X/Y/Z
void Camera::translate(glm::vec3 v)
{
	glm::vec4 pos(position, 1.0);
	glm::vec4 look(lookDirection, 1.0);
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), v);
	pos = matrix * pos;
	look = matrix * look;

	position = pos.xyz();
	lookDirection = look.xyz();

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
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

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
}



// Yaw the camera along the up vector
void Camera::yaw(float theta)
{
	glm::vec4 look(lookDirection, 0.0);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), theta, upVector);
	look = matrix * look;
	lookDirection = look.xyz();

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
}



// Roll the camera along the look axis
void Camera::roll(float theta)
{
	glm::vec4 up(upVector, 0.0);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), theta, lookDirection);
	up = matrix * up;
	upVector = up.xyz();

	std::cout << "{" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "}, {" << position.x << ", " << position.y << ", " << position.z << "}, {" << upVector.x << ", " << upVector.y << ", " << upVector.z << "}" << std::endl;
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



// Render the scene with the current camera settings
void Camera::render()
{
	if (scene)
		scene->render(position, lookDirection, upVector, projection);
}
