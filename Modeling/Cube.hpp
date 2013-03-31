
#ifndef CUBE_HPP
#define CUBE_HPP

#include "Mesh.hpp"
#include <memory>

class Cube
{
	public:
		std::shared_ptr<Mesh> getMesh();

	private:
		void setVertices(std::shared_ptr<Mesh>& mesh);
		void setIndices(std::shared_ptr<Mesh>& mesh);
		void setTexture(std::shared_ptr<Mesh>& mesh);
};

#endif

/*

GLuint mytex[1];
glGenTextures(1, mytex);

glBindTexture(GL_TEXTURE_2D, mytex[0]);

 */


/*

#define N 36
GLfloat tex_coord[N][2];

 */
