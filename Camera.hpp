#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/freeglut.h>

class Camera
{
	public:
		Camera(float xAngle, float yAngle, float yAngle);
		void rotateCameraX(float theta);
		void rotateCameraY(float theta);
		void rotateCameraZ(float theta);
		//todo: add location info

	private:
		void ensureRotationRange(float& value);

		GLfloat rotation[3];

		enum CameraAxis
		{
			X_AXIS = 0,
			Y_AXIS = 1,
			Z_AXIS = 2
		};
};

#endif
