

cameraAngle = glGetUniformLocation(program, "cameraAngle");

void init()
{

}



void render()
{
	glUniform3fv(cameraAngle, 1, rotation); //apply view angle
	glDrawArrays(GL_POINTS, 0, res * res);
}
	


void World::rotateCameraX(float theta)
{
	cameraAngle[X_AXIS] += theta;
	ensureRotationRange(cameraAngle[X_AXIS]);
}



void World::rotateCameraY(float theta)
{
	cameraAngle[Y_AXIS] += theta;
	ensureRotationRange(cameraAngle[Y_AXIS]);
}



void World::rotateCameraZ(float theta)
{
	cameraAngle[Z_AXIS] += theta;
	ensureRotationRange(cameraAngle[Z_AXIS]);
}



/* Ensures that 'value' is in the range of [0, 360) */
void World::ensureRotationRange(float& value)
{
	while (value >= 360.0)
		value -= 360.0;

	while (value < 0)
		value += 360.0;
}