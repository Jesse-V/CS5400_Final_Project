
#include "Model.hpp"
#include <iostream> //temp
#include "ShaderLoader.hpp"
#include <exception>


Model::Model():
	program(0), vertexCount(0)
{}



GLuint Model::getProgram()
{
	return program;
}




#include "Model.hpp"


Model::Model(const Mesh& mesh):
	mesh(mesh)
{}



void render(const Camera& camera)
{
	mesh.render(camera, location);
}
