
#include "Scene.hpp"
#include "Modeling/Cube.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>


void Scene::init()
{
	program = cs5400::make_program(cs5400::make_vertexShader("Shaders/vertex.glsl"), cs5400::make_fragmentShader("Shaders/fragment.glsl"));
	GLuint handle = program->getHandle();

	vertexAttrib			= glGetAttribLocation(handle, "vertex");
	vertexNormalAttrib		= glGetAttribLocation(handle, "vertexNormal");

	modelMatrixUniform		= glGetUniformLocation(handle, "matrixModel");
	viewMatrixUniform       = glGetUniformLocation(handle, "viewMatrix");
	projMatrixUniform		= glGetUniformLocation(handle, "projMatrix");
	lightPosUniform			= glGetUniformLocation(handle, "worldLightPos");

	ambientLightUniform		= glGetUniformLocation(handle, "ambientLight");
}



void Scene::addModel(const RenderableObject& obj)
{
	/*Cube cube;
	std::shared_ptr<Mesh> mesh = cube.getMesh();

	RenderableObject obj(program->getHandle(), mesh);*/
	obj.setModelMatrix(glm::translate(glm::mat4(), glm::vec3(0.0, -0.1, 0.0)));
	objects.push_back(obj);
}



void Scene::setCamera(const std::shared_ptr<Camera>& sceneCamera)
{
	camera = sceneCamera;
}



void Scene::addLight(const std::shared_ptr<Light>& light)
{
	lights.push_back(light);
}



void Scene::setAmbientLight(const glm::vec3& rgb)
{
	ambientLight = rgb;
}



// Render the scene as it currently is
void Scene::render(/*const glm::vec3& eyePosition, const glm::vec3& lookDirection, const glm::vec3& upVector, const glm::mat4& projMatrix*/)
{
	glUseProgram(program->getHandle());

	glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(), camera->getLookDirection(), camera->getUpVector());
	glm::vec3 lightPos = lights[0]->getPosition(); //todo: support for multiple lights

	// pass our transformation matricies to the shaders
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

	// tell the shaders where the light is
	glUniform3f(lightPosUniform, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(ambientLightUniform, ambientLight.x, ambientLight.y, ambientLight.z);

	// now render each object
	for_each (objects.begin(), objects.end(),
		[&](RenderableObject& obj)
		{
			obj.render(modelMatrixUniform);
		});
}



std::shared_ptr<Camera> Scene::getCamera()
{
	return camera;
}



std::shared_ptr<cs5400::Program> Scene::getProgram()
{
	return program;
}
