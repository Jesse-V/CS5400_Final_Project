#ifndef WORLD_HPP
#define WORLD_HPP

class World
{
	public:
		void init();
		void render();
		void rotateCameraX(float theta);
		void rotateCameraY(float theta);
		void rotateCameraZ(float theta);
	
	private:
		const int ROTATION_SPEED = 1;
		const float ZOOM = 0.7f;
		GLfloat rotation[3] = {114, 0, 16}; //initial view
		GLuint cameraAngle;
		
		void ensureRotationRange(float& value);
}