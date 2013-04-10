
#include "World/Scene.hpp"
#include "World/Camera.hpp"
#include "CustomObjects/Ground.hpp"
#include "CustomObjects/Mandelbrot.hpp"
#include <iostream>
#include <thread>


const float ROTATION_SPEED = 0.015;
const float TRANSLATION_SPEED = 1.1;
const float LIGHT_MOVEMENT_SPEED = 0.007f;

Scene scene;
std::shared_ptr<Light> light = std::make_shared<Light>();


/*	Causes the current thread to sleep for the specified number of milliseconds */
void sleep(int milliseconds)
{
	std::chrono::milliseconds duration(milliseconds);
	std::this_thread::sleep_for(duration); //forget time.h or windows.h, this is the real way to sleep!
}



void onDisplay()
{
	glClearColor(.39f, 0.58f, 0.93f, 0.0f);	//nice blue background
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	scene.render();

	glm::vec3 lightPos = light->getPosition();
	lightPos.x += LIGHT_MOVEMENT_SPEED;
	lightPos.y += LIGHT_MOVEMENT_SPEED;
	lightPos.z += LIGHT_MOVEMENT_SPEED;
	light->setPosition(lightPos);

	glutSwapBuffers();
	sleep(50); //20 fps
	glutPostRedisplay();
}



void onKey(unsigned char key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case 'w':
			camera->moveY(ROTATION_SPEED);
			break;

		case 's':
			camera->moveY(-ROTATION_SPEED);
			break;

		case 'a':
			camera->moveX(-ROTATION_SPEED);
			break;

		case 'd':
			camera->moveX(ROTATION_SPEED);
			break;

		case 'q':
			camera->moveZ(ROTATION_SPEED);
			break;

		case 'e':
			camera->moveZ(-ROTATION_SPEED);
			break;
	}

	std::cout << camera->toString() << std::endl;
}



void onSpecialKey(int key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case GLUT_KEY_UP:
			camera->pitch(TRANSLATION_SPEED);
			break;

		case GLUT_KEY_DOWN:
			camera->pitch(-TRANSLATION_SPEED);
			break;

		case GLUT_KEY_LEFT:
			camera->yaw(TRANSLATION_SPEED);
			break;

		case GLUT_KEY_RIGHT:
			camera->yaw(-TRANSLATION_SPEED);
			break;

		case GLUT_KEY_PAGE_UP:
			camera->roll(-TRANSLATION_SPEED);
			break;

		case GLUT_KEY_PAGE_DOWN:
			camera->roll(TRANSLATION_SPEED);
			break;
	}

	std::cout << camera->toString() << std::endl;
}



/*
void onMouseClick(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			mouseDown = true;
			break;

		default:
			mouseDown = false;
	}
}



void onMouseMotion(int x, int y)
{
	camera->pitchAndRoll(x, y); //TODO: cleanup
}*/



/* Initializes glut. Sets the window size and title to the specified values */
void initializeGlutWindow(int width, int height, const std::string& windowTitle)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle.c_str());
}


void addGround()
{
	Ground ground;
	RenderableObject rObj(scene.getProgram()->getHandle(), ground.getDataBuffers());
	scene.addModel(rObj);
}


void addMandelbrot()
{
	Mandelbrot mandelbrot;
	RenderableObject rObj(scene.getProgram()->getHandle(), mandelbrot.getDataBuffers());
	scene.addModel(rObj);
}



void addModels()
{
	//addGround();
	addMandelbrot();
}



void addLight()
{
	scene.setAmbientLight(glm::vec3(0.3, 0, 0));
	light->setPosition(glm::vec3(0.3f, -1.7f, -0.5f));
	scene.addLight(light); //todo: send light color and power to GPU
}



void addCamera()
{
	auto camera = std::make_shared<Camera>();
	camera->lookAt(glm::vec3(-0.157905, -0.328774, -0.931114), glm::vec3(-0.080037, 0.877983, -0.471953));
	camera->setPosition(glm::vec3(0.117748, 0.164188, 1.5894));
	scene.setCamera(camera);
}



void initializeApplication()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	scene.init();

	addModels();
	addLight();
	addCamera();
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	initializeGlutWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), "Final OpenGL Project - Jesse Victors");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	try
	{
		glutDisplayFunc(onDisplay);
		glutKeyboardFunc(onKey);
		glutSpecialFunc(onSpecialKey);

		//glutMotionFunc(onMouseMotion);
		//glutMouseFunc(onMouseClick);

		initializeApplication();
		glutMainLoop();

	}
	catch (std::exception& e)
	{
		std::cerr << std::endl;
		std::cerr << e.what();
		std::cerr << std::endl;
	}

	return EXIT_SUCCESS;
}
