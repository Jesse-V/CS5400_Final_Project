#include <chrono>
#include <thread>
#include <cmath>
#include <vector>

#include "ShaderLoader.h"
#include "Triangle.struct"

const int ROTATION_SPEED = 1;
const float ZOOM = 0.7f;
GLfloat rotation[3] = {114, 0, 16}; //initial view

GLuint cameraAngle;

int res = 512;










/* Fetches the model and puts it into GPU memory */
void init()
{
	

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}



/* Clears the screen, applies view angle, and renders the model */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUniform3fv(cameraAngle, 1, rotation); //apply view angle
	glDrawArrays(GL_POINTS, 0, res * res);
	
	glutSwapBuffers();
}



/* Ensures that 'value' is in the range of [0, 360) */
void modRotation(float& value)
{
	while (value >= 360.0)
		value -= 360.0;

	while (value < 0)
		value += 360.0;
}



/*	Handles keyboard input. Does rotation according to user input */
void keyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			rotation[0] += ROTATION_SPEED; //add to X axis
			break;

		case 's':
			rotation[0] -= ROTATION_SPEED; //subtract from X axis
			break;

		case 'd':
			rotation[1] += ROTATION_SPEED; //add to Y axis
			break;

		case 'a':
			rotation[1] -= ROTATION_SPEED; //subtract from Y axis
			break;

		case 'e':
			rotation[2] += ROTATION_SPEED; //add to Z axis
			break;

		case 'q':
			rotation[2] -= ROTATION_SPEED; //subtract from Z axis
			break;
	}

	modRotation(rotation[0]);
	modRotation(rotation[1]);
	modRotation(rotation[2]);
}



/*	Causes the current thread to sleep for the specified number of milliseconds */
void sleep(int milliseconds)
{
	std::chrono::milliseconds duration(milliseconds);
	std::this_thread::sleep_for(duration); //forget time.h or windows.h, this is the real way to sleep!
}



/* 	Called when Glut has nothing else to do.
	This waits to preserve framerate, and then redisplays the model. */
void onIdle()
{
	sleep(50); //20 fps
	glutPostRedisplay();
}



/* Initializes glut. Sets the window size and title to the specified values */
void initializeGlutWindow(int width, int height, const std::string& windowTitle)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle.c_str());
}


/*	Entry point for the program.
	Initializes glut, the window, and the shaders, and then begins rendering the model. */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	int windowHeight = glutGet(GLUT_SCREEN_HEIGHT) - 20;
	initializeGlutWindow(windowHeight, windowHeight, "OpenGL Application by Jesse Victors");

	glewInit();
	init();

	glutDisplayFunc(render);
	glutKeyboardFunc(keyboardInput);
	glutIdleFunc(onIdle);

	glutMainLoop();
	return 0;
}