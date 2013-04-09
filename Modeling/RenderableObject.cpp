
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <vector>
#include <algorithm>


RenderableObject::RenderableObject(GLuint program, const std::vector<DataBuffer>& dataBuffers):
	modelMatrix(glm::mat4(1.0)), isVisible(true), dataBuffers(dataBuffers)
{
	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const DataBuffer& buffer)
		{
			buffer.initialize(program);
		});

	//glm::translate(glm::mat4(), glm::vec3(0.0, -0.1, 0.0))
	//glm::mat4(1.0)
}



// Objects that are not 'visible' will not be rendered
void RenderableObject::setVisible(bool visible)
{
	isVisible = visible;
}



// Set the matrix to convert from model coords to world coords
void RenderableObject::setModelMatrix(const glm::mat4& matrix)
{
	modelMatrix = matrix;
}



// Render the object
void RenderableObject::render(GLuint modelMatrixID)
{
	if (isVisible)
	{
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		enableDataBuffers();
		glDrawElements(GL_TRIANGLES, mesh->triangles.size() * 3, GL_UNSIGNED_INT, 0);
		disableDataBuffers();
	}
}



void RenderableObject::enableDataBuffers()
{
	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const DataBuffer& buffer)
		{
			buffer.enable();
		});
}



void RenderableObject::disableDataBuffers()
{
	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const DataBuffer& buffer)
		{
			buffer.disable();
		});
}
