
#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "DataBuffers/DataBuffer.hpp"

class RenderableObject
{
	public:
		RenderableObject(GLuint program, const std::vector<DataBuffer>& dataBuffers);
		void setVisible(bool visible);
		void setModelMatrix(const glm::mat4& matrix); // model coords -> world coords matrix
		void render(GLuint modelMatrixID);

	private:
		std::vector<DataBuffer> dataBuffers;
		glm::mat4 modelMatrix;
		bool isVisible;
};

#endif
