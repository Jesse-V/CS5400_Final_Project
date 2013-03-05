
#include "Model.hpp"
#include <iostream> //temp
#include "ShaderLoader.hpp"
#include <exception>


Model::Model():
	program(0), vertexCount(0)
{
	bindVertices();
}



GLuint Model::getProgram()
{
	return program;
}



void Model::bindVertices()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::cout << "vao: " << vao << std::endl;
}



void Model::storeVertices(std::vector<Point> vertices)
{
	vertexCount = vertices.size();
	int memSize = vertexCount * sizeof(Point);
	
	GLuint buffer; //pointer to the GPU memory
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, memSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, memSize, vertices.data()); //save vertices

	std::cout << "buffer: " << buffer << std::endl;
}



void Model::initializeProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	program = initShader(vertexShader.c_str(), fragmentShader.c_str());
	glUseProgram(program);
	initVertexPositionAttribute(program);
}



void Model::initVertexPositionAttribute(const GLuint& prog)
{
	GLuint vertPosition = glGetAttribLocation(prog, "vertPosition");
	glEnableVertexAttribArray(vertPosition);
	glVertexAttribPointer(vertPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}



int Model::getVertexCount()
{
	return vertexCount;
}
