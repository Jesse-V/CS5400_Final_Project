
#include "Model.hpp"
#include <iostream> //temp
#include "ShaderLoader.hpp"
#include <exception>


Model::Model()
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
}



void Model::storeVertices(std::vector<Point> vertices)
{
	GLuint buffer; //pointer to the GPU memory
	int size = vertices.size() * sizeof(Point);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices.data()); //save vertices
}



void Model::initializeProgram()
{
	program = initShader("Mandelbrot/vertex.glsl", "Mandelbrot/fragment.glsl");
	glUseProgram(program);
	initVertexPositionAttribute(program);
}



void Model::initVertexPositionAttribute(const GLuint& program)
{
	GLuint vertPosition = glGetAttribLocation(program, "vertPosition");
	glEnableVertexAttribArray(vertPosition);
	glVertexAttribPointer(vertPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}
