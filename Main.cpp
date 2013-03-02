#include <chrono>
#include <thread>
#include <cmath>
#include <vector>

#include "ShaderLoader.h"
#include "Triangle.struct"

const int ROTATION_SPEED = 1;
World world();


/* Fetches the model and puts it into GPU memory */
void init()
{
	world.init();
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}



/* Clears the screen, applies view angle, and renders the model */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world.render();	
	glutSwapBuffers();
}



/*	Handles keyboard input. Does rotation according to user input */
void handleKeyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			world.rotateCameraX(ROTATION_SPEED);
			break;

		case 's':
			world.rotateCameraX(-ROTATION_SPEED);
			break;

		case 'd':
			world.rotateCameraY(ROTATION_SPEED);
			break;

		case 'a':
			world.rotateCameraX(-ROTATION_SPEED);
			break;

		case 'e':
			world.rotateCameraZ(ROTATION_SPEED);
			break;

		case 'q':
			world.rotateCameraX(-ROTATION_SPEED);
			break;
	}
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