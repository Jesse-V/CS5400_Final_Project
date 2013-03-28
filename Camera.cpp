
#include "Camera.hpp"


void World::setViewAngle(float x, float y, float z)
{
	rotation[X_AXIS] = x;
	rotation[Y_AXIS] = y;
	rotation[Z_AXIS] = z;
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
	while (value >= 360.0f)
		value -= 360.0f;

	while (value < 0)
		value += 360.0f;
}
