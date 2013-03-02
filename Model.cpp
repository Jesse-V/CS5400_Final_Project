
#include "Model.hpp"


Model::Model():
{
	bindVertices();
	storeVertices(getVertices());
	initializeProgram();
}


GLuint Model::getProgram()
{
	return program;
}


std::vector<Point> Model::getVertices()
{
	std::cout << "DERP!!!!" << std::endl;

	std::vector<Point> vertices;
	return vertices;
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



void Model::bindVertices()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
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