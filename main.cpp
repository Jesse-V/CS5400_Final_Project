
#include "Scene.hpp"
#include "Camera.hpp"
#include <iostream>


Scene scene;
Camera camera;


void onDisplay()
{
	// Clear the background as black
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// render the scene
	camera.render();

	// Display the newly rendered image to the screen
	glutSwapBuffers();
}


void onKey(unsigned char key, int, int)
{
	switch(key)
	{
		case 'w':  camera.moveY( 0.01);  break;
		case 's':  camera.moveY(-0.01);  break;
		case 'a':  camera.moveX(-0.01);  break;
		case 'd':  camera.moveX( 0.01);  break;
		case 'q':  camera.moveZ( 0.01);  break;
		case 'e':  camera.moveZ(-0.01);  break;
	}

	glutPostRedisplay();
}


void onSpecialKey(int key, int, int)
{
	switch(key)
	{
		case GLUT_KEY_UP:        camera.pitch( 1.0); break;
		case GLUT_KEY_DOWN:      camera.pitch(-1.0); break;
		case GLUT_KEY_LEFT:      camera.yaw( 1.0);   break;
		case GLUT_KEY_RIGHT:     camera.yaw(-1.0);   break;
		case GLUT_KEY_PAGE_UP:   camera.roll(-1.0);  break;
		case GLUT_KEY_PAGE_DOWN: camera.roll( 1.0);  break;
	}

	glutPostRedisplay();
}



int main(int argc, char **argv)
{
	// Glut-related initialising functions
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("hw2");

	std::cout << "\n\n\t***********************************\n";
	std::cout <<     "\t* See README file for camera keys *\n";
	std::cout <<     "\t***********************************\n\n\n";

	// Extension wrangler initialising
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	try {
		glutDisplayFunc(onDisplay);
		glutKeyboardFunc(onKey);
		glutSpecialFunc(onSpecialKey);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		scene.init();
		scene.loadCubeModel();
		camera.setScene(std::make_shared<Scene>(scene));
		glutMainLoop();

	} catch (std::exception &e) {
		std::cerr << std::endl << std::endl << e.what() << std::endl << std::endl;
	}

	return EXIT_SUCCESS;
}
