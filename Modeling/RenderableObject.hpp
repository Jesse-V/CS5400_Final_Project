
#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "Mesh.hpp"

// This is the base class for any object that is to
// be rendered in the scene.  It knows how to render
// itself

class RenderableObject
{
	public:
		RenderableObject(GLuint program, const std::shared_ptr<Mesh>& mesh);
		void setVisible(bool visible);
		void setModelMatrix(const glm::mat4& matrix); // model coords -> world coords matrix
		void render(GLuint modelmatrixid);
		std::shared_ptr<Mesh> getMesh() const;

	private:
		void storePoints();
		void storeNormals();
		void storeMesh();
		void storeTexture();

	private:
		std::shared_ptr<Mesh> mesh;
		glm::mat4 modelMatrix;
		bool isVisible;

		GLuint vertexBuffer, normalBuffer, meshBuffer;//, textureBuffer;
		GLint vertexAttrib, normalAttrib, textureAttrib;

		GLuint texture, buffer, vTexCoord;
};

#endif
