
#ifndef MESH_HPP
#define MESH_HPP

#include "Camera.hpp"
#include "Triangle.struct"

class Mesh
{
	public:
		void render(const Camera& camera, const Point& location);

	private:
		//GLuint program;
		//GLint attribute_coord2d;
		//std::shared_ptr<cs5400::Program> program;


		GLuint indexBuffer;

		//holds index buffer, texture buffer, vertex buffer, program, etc.
		//Todo later: store these more efficiently
/*
	public:
		GLuint getProgram();
		virtual std::vector<Point> getVertices() = 0;
		int getVertexCount();

	protected:
		Model();
		void initializeProgram(const std::string& vertexShader, const std::string& fragmentShader);
		void bindVertices();
		void storeVertices(std::vector<Point> vertices);
		void initVertexPositionAttribute(const GLuint& program);

		GLuint program;
		int vertexCount;*/
};

#endif
