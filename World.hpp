#ifndef WORLD_HPP
#define WORLD_HPP

#include "ShaderLoader.hpp"
#include "Model.hpp"
#include "Triangle.struct"

class World
{
	public:
		void init(const Model& model);
		void render();
		void rotateCameraX(float theta);
		void rotateCameraY(float theta);
		void rotateCameraZ(float theta);
	
	private:
		const int ROTATION_SPEED = 1;
		const float ZOOM = 0.7f;
		GLfloat rotation[3] = {114, 0, 16}; //initial view
		GLuint cameraAngle;
		Model model;

		void ensureRotationRange(float& value);

		enum CameraAxis
		{
			X_AXIS = 0,
			Y_AXIS = 1,
			Z_AXIS = 2
		};
};

#endif