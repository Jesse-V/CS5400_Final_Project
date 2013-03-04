#ifndef WORLD_HPP
#define WORLD_HPP

#include "Model.hpp"
#include <memory>

class World
{
	public:
		void addModel(std::shared_ptr<Model> model);
		void render();
		void rotateCameraX(float theta);
		void rotateCameraY(float theta);
		void rotateCameraZ(float theta);
	
	private:
		const int ROTATION_SPEED = 1;
		const float ZOOM = 0.7f;
		GLfloat rotation[3] = {114, 0, 16}; //initial view
		GLuint cameraAngle;
		std::shared_ptr<Model> model;

		void ensureRotationRange(float& value);

		enum CameraAxis
		{
			X_AXIS = 0,
			Y_AXIS = 1,
			Z_AXIS = 2
		};
};

#endif