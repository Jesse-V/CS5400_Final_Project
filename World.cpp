#include "World.hpp"



void World::init()
{
	model = new Model();
}



void World::render()
{
	int res = 512; //todo: this is a hack

	cameraAngle = glGetUniformLocation(model->getProgram(), "cameraAngle");
	glUniform3fv(cameraAngle, 1, rotation); //apply view angle
	glDrawArrays(GL_POINTS, 0, res * res);
}
	


void World::rotateCameraX(float theta)
{
	rotation[X_AXIS] += theta;
	ensureRotationRange(rotation[X_AXIS]);
}



void World::rotateCameraY(float theta)
{
	rotation[Y_AXIS] += theta;
	ensureRotationRange(rotation[Y_AXIS]);
}



void World::rotateCameraZ(float theta)
{
	rotation[Z_AXIS] += theta;
	ensureRotationRange(rotation[Z_AXIS]);
}



/* Ensures that 'value' is in the range of [0, 360) */
void World::ensureRotationRange(float& value)
{
	while (value >= 360.0)
		value -= 360.0;

	while (value < 0)
		value += 360.0;
}