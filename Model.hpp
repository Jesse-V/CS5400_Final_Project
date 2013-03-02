#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include "Triangle.struct"

class Model
{
	public:
		Model();
		GLuint getProgram();
		std::vector<Point> getVertices();

	private:
		GLuint program;
		
		void initializeProgram();
		void bindVertices();
		void storeVertices(std::vector<Point> vertices);
		void initVertexPositionAttribute(const GLuint& program);
};

#endif