
#include "Program.hpp"


cs5400::Program::Program(std::shared_ptr<VertexShader> vertex_, std::shared_ptr<FragmentShader> fragment_):
	handle(glCreateProgram()), vertex(vertex_), fragment(fragment_)
{}



cs5400::Program::~Program()
{
	glDeleteProgram(handle);
}



GLuint cs5400::Program::getHandle()
{
	return handle;
}



std::shared_ptr<cs5400::Program> cs5400::makeProgram(std::shared_ptr<cs5400::VertexShader> vertex, std::shared_ptr<cs5400::FragmentShader> fragment)
{
	GLint link_ok = GL_FALSE;
	auto program = std::make_shared<Program>(vertex, fragment);

	glAttachShader(program->getHandle(), vertex->getHandle());
	glAttachShader(program->getHandle(), fragment->getHandle());
	glLinkProgram(program->getHandle());
	glGetProgramiv(program->getHandle(), GL_LINK_STATUS, &link_ok);

	if (!link_ok)
		throw std::runtime_error("Could not link shader program.");

	return program;
}
