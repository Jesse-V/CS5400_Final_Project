
#include "Application.hpp"
#include "CustomObjects/Ground/Ground.hpp"
#include "CustomObjects/Mandelbrot/Mandelbrot.hpp"
#include <thread>


Application::Application()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	addModels();
	addLight();
	addCamera();
}



void Application::render()
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



void Application::onKey(unsigned char key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case 'a':
			camera->translateX(-TRANSLATION_SPEED);
			break;

		case 'd':
			camera->translateX(TRANSLATION_SPEED);
			break;

		case 'q':
			camera->translateY(-TRANSLATION_SPEED);
			break;

		case 'e':
			camera->translateY(TRANSLATION_SPEED);
			break;

		case 'w':
			camera->translateZ(-TRANSLATION_SPEED);
			break;

		case 's':
			camera->translateZ(TRANSLATION_SPEED);
			break;
	}

	//std::cout << camera->toString() << std::endl;
}



void Application::onSpecialKey(int key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case GLUT_KEY_UP:
			camera->pitch(ROTATION_SPEED);
			break;

		case GLUT_KEY_DOWN:
			camera->pitch(-ROTATION_SPEED);
			break;

		case GLUT_KEY_LEFT:
			camera->yaw(ROTATION_SPEED);
			break;

		case GLUT_KEY_RIGHT:
			camera->yaw(-ROTATION_SPEED);
			break;

		case GLUT_KEY_PAGE_UP:
			camera->roll(-ROTATION_SPEED);
			break;

		case GLUT_KEY_PAGE_DOWN:
			camera->roll(ROTATION_SPEED);
			break;
	}

	//std::cout << camera->toString() << std::endl;
}



void Application::addGround()
{
	Ground ground;
	auto rObj = ground.makeObject();

	glm::mat4 objMatrix = glm::mat4();
	objMatrix = glm::scale(objMatrix, glm::vec3(2, 1, 2));
	objMatrix = glm::translate(objMatrix, glm::vec3(0, -0.15, 0));
	rObj->setModelMatrix(objMatrix);

	scene.addModel(rObj);
}



void Application::addMandelbrot()
{
	Mandelbrot mandelbrot;
	auto rObj = mandelbrot.makeObject();

	glm::mat4 objMatrix = glm::mat4();
	objMatrix = glm::scale(objMatrix, glm::vec3(1, 1, 2));
	objMatrix = glm::translate(objMatrix, glm::vec3(0, 0, -0.5));
	objMatrix = glm::rotate(objMatrix, 120.0f, glm::vec3(0, 0, 1));
	rObj->setModelMatrix(objMatrix);

	scene.addModel(rObj);
}



void Application::addModels()
{
	addGround();
	addMandelbrot();
}



void Application::addLight()
{
	scene.setAmbientLight(glm::vec3(0.2, 0.2, 0.2));
	light->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	scene.addLight(light); //todo: send light color and power to GPU
}



void Application::addCamera()
{
	auto camera = std::make_shared<Camera>();
	camera->lookAt(glm::vec3(-0.041535, -0.813947, -0.579453), glm::vec3(-0.0114782, 0.590822, -0.80672));
	camera->setPosition(glm::vec3(0.0318538, 0.331304, 2.59333));
	scene.setCamera(camera);
}



/*	Causes the current thread to sleep for the specified number of milliseconds */
void Application::sleep(int milliseconds)
{
	std::chrono::milliseconds duration(milliseconds);
	std::this_thread::sleep_for(duration); //forget time.h or windows.h, this is the real way to sleep!
}
