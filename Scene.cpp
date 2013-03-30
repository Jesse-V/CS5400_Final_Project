
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

	// Set the default ambient light
	setAmbientLight(glm::vec3(0.12, 0.1, 0.1));
}


//todo: addModel
void Scene::loadCubeModel(glm::mat4 modelMatrix)
{
	Cube cube;
	std::shared_ptr<Mesh> mesh = cube.getMesh();

	RenderedObject obj(program->getHandle(), mesh);
	obj.setModelMatrix(modelMatrix);
	objects.push_back(obj);
}



void Scene::addLight(const Light &light)
{
	lights.push_back(light);
}



void Scene::setAmbientLight(glm::vec3 rgb)
{
	ambientLight = rgb;
}



// Render the scene as it currently is
void Scene::render(const glm::vec3& eyePosition, const glm::vec3& lookDirection, const glm::vec3& upVector, const glm::mat4& projMatrix)
{
	glUseProgram(program->getHandle());

	glm::mat4 viewMatrix    = glm::lookAt(eyePosition, lookDirection, upVector);
	glm::vec3 lightPos = glm::vec3(-0.3f, 1.7f, 0.5f);

	// pass our transformation matricies to the shaders
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE, glm::value_ptr(projMatrix));

	// tell the shaders where the light is
	glUniform3f(lightPosUniform, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(ambientLightUniform, ambientLight.x, ambientLight.y, ambientLight.z);

	// now render each object
	for_each (objects.begin(), objects.end(),
		[&](RenderedObject& obj)
		{
			obj.render(modelMatrixUniform);
		});
}
