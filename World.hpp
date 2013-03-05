#ifndef WORLD_HPP
#define WORLD_HPP

#include "Model.hpp"
#include <memory>
#include <vector>

class World
{
	public:
		World();
		void render();
		void addModel(const std::shared_ptr<Model>& model);
		void setViewAngle(float xAxis, float yAxis, float zAxis);
		void rotateCameraX(float theta);
		void rotateCameraY(float theta);
		void rotateCameraZ(float theta);
	
	private:
		GLfloat rotation[3];
		std::vector<std::shared_ptr<Model>> models;

		void ensureRotationRange(float& value);

		enum CameraAxis
		{
			X_AXIS = 0,
			Y_AXIS = 1,
			Z_AXIS = 2
		};
};

#endif
