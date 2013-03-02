#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include "Triangle.struct"

class Program
{
	public:
		Program();
		GLuint getProgram();
		std::vector<Point> getVertices();

	private:
		Gluint program;
		
		void initializeProgram();
		void bindVertices();
		void storeVertices(std::vector<Point> vertices);
		void initVertexPositionAttribute(const GLuint& program);
};

#endif