#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Scene.hpp"
#include "glm/glm.hpp"
#include <memory>


class Camera
{
	public:
		Camera(const std::shared_ptr<Scene>& scene = NULL);

		void setScene(const std::shared_ptr<Scene>& scene);

		// resets the camera to defaults
		void reset();

		// Functions to move/direct the camera
		void setPosition(glm::vec3 pos);
		void lookAt(glm::vec3 look, glm::vec3 up = glm::vec3(0.0, 1.0, 0.0));

		void moveX(float units);
		void moveY(float units);
		void moveZ(float units);

		void translate(glm::vec3 v);
		void roll(float theta);
		void pitch(float theta);
		void yaw(float theta);

		// Set the perspective of the camera and its clipping distances
		void setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearclip, float farclip);

		// Individually set any of the perspective fields
		void setFieldOfView(float degrees);
		void setAspectRatio(float ratio);
		void setNearFieldClipDistance(float distance);
		void setFarFieldClipDistance(float distance);

		void render();

	private:
		std::shared_ptr<Scene> scene;

		glm::vec3 lookDirection, position, upVector;
		float fieldOfView, aspectRatio, nearFieldClip, farFieldClip;
		glm::mat4 projection;
};

#endif

