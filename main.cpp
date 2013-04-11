
#include "World/Scene.hpp"
#include "World/Camera.hpp"
#include "CustomObjects/Ground.hpp"
#include "CustomObjects/Mandelbrot.hpp"
#include <iostream>
#include <thread>


const float ROTATION_SPEED = 0.015;
const float TRANSLATION_SPEED = 1.1;
const glm::vec3 LIGHT_VECTOR = glm::vec3(0.0f, 0.0f, -0.01f);

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
	lightPos += LIGHT_VECTOR;
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
		case 'a':
			camera->translateX(-ROTATION_SPEED);
			break;

		case 'd':
			camera->translateX(ROTATION_SPEED);
			break;

		case 'q':
			camera->translateY(-ROTATION_SPEED);
			break;

		case 'e':
			camera->translateY(ROTATION_SPEED);
			break;

		case 'w':
			camera->translateZ(-ROTATION_SPEED);
			break;

		case 's':
			camera->translateZ(ROTATION_SPEED);
			break;
	}

	//std::cout << camera->toString() << std::endl;
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

	//std::cout << camera->toString() << std::endl;
}



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
	std::shared_ptr<cs5400::Program> program = cs5400::makeProgram(cs5400::makeVertexShader("Shaders/Ground/vertex.glsl"), cs5400::makeFragmentShader("Shaders/Ground/fragment.glsl"));

	RenderableObject rObj(program, ground.getDataBuffers());

	glm::mat4 objMatrix = glm::mat4();
	objMatrix = glm::scale(objMatrix, glm::vec3(3, 1, 3));
	objMatrix = glm::translate(objMatrix, glm::vec3(0, -0.15, 0));
	rObj.setModelMatrix(objMatrix);

	scene.addModel(rObj);
}



void addMandelbrot()
{
	Mandelbrot mandelbrot;
	std::shared_ptr<cs5400::Program> program = cs5400::makeProgram(cs5400::makeVertexShader("Shaders/Mandelbrot/vertex.glsl"), cs5400::makeFragmentShader("Shaders/Mandelbrot/fragment.glsl"));
	RenderableObject rObj(program, mandelbrot.getDataBuffers());

	glm::mat4 objMatrix = glm::mat4();
	objMatrix = glm::scale(objMatrix, glm::vec3(1, 1, 2));
	objMatrix = glm::rotate(objMatrix, 120.0f, glm::vec3(0, 0, 1));
	rObj.setModelMatrix(objMatrix);

	scene.addModel(rObj);
}



void addModels()
{
	addGround();
	addMandelbrot();
}



void addLight()
{
	scene.setAmbientLight(glm::vec3(0.2, 0.2, 0.2));
	light->setPosition(glm::vec3(0.0f, 0.0f, 3.0f)); //light->setPosition(glm::vec3(0.3f, -1.7f, -0.5f));
	scene.addLight(light); //todo: send light color and power to GPU
}



void addCamera()
{
	auto camera = std::make_shared<Camera>();
	camera->lookAt(glm::vec3(-0.041535, -0.813947, -0.579453), glm::vec3(-0.0114782, 0.590822, -0.80672));
	camera->setPosition(glm::vec3(0.0318538, 0.331304, 2.59333));
	scene.setCamera(camera);
}



void initializeApplication()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	addModels();
	addLight();
	addCamera();
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	initializeGlutWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), "Final OpenGL Project - Jesse Victors");
	std::cout << "hello1" << std::endl;

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
		std::cout << "Launching application..." << std::endl;
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
