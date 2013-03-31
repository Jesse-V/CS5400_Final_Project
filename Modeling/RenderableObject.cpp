
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <vector>
#include <algorithm>


RenderableObject::RenderableObject(GLuint program, const std::shared_ptr<Mesh>& mesh):
	mesh(mesh), modelMatrix(glm::mat4(1.0)), isVisible(true)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &normalBuffer);
	glGenBuffers(1, &meshBuffer);
	glGenBuffers(1, &textureBuffer);

	vertexAttrib = glGetAttribLocation(program, "vertex");
	normalAttrib = glGetAttribLocation(program, "vertexNormal");
	textureAttrib = glGetAttribLocation(program, "textureCoord");

	storePoints();
	storeNormals();
	storeMesh();
}



// Store the vertices in a GPU buffer
void RenderableObject::storePoints()
{
	const std::vector<glm::vec3> &verts = mesh->vertices;

	std::vector<GLfloat> rawpoints;
	for_each (verts.begin(), verts.end(),
		[&](const glm::vec3& v)
		{
			rawpoints.push_back(v.x);
			rawpoints.push_back(v.y);
			rawpoints.push_back(v.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawpoints.size()*sizeof(GLfloat), rawpoints.data(), GL_STATIC_DRAW);
}



// Store the normals in a GPU buffer
void RenderableObject::storeNormals()
{
	std::vector<GLfloat> rawNormals;
	for_each (mesh->normals.begin(), mesh->normals.end(),
		[&](const glm::vec3& n)
		{
			rawNormals.push_back(n.x);
			rawNormals.push_back(n.y);
			rawNormals.push_back(n.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawNormals.size() * sizeof(GLfloat), rawNormals.data(), GL_STATIC_DRAW);
}



// Store the mesh in a GPU buffer
void RenderableObject::storeMesh()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->triangles.size() * 3 * sizeof(GLuint), mesh->triangles.data(), GL_STATIC_DRAW);
}



// Send the texture map to the GPU
void RenderableObject::storeTextureMap()
{

}



// Rotate the object along the arbitrary axis, by 'theta' degrees
void RenderableObject::rotate(const glm::vec3& axis, double theta)
{

}



// Move the object along the x, y, and z axes in the amount specified
void RenderableObject::translate(const glm::vec3& xyz)
{

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
void RenderableObject::render(GLuint modelmatrixid)
{
	// Don't render if it's been flagged as not visible
	if (!isVisible)
		return;

	glUniformMatrix4fv(modelmatrixid, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glEnableVertexAttribArray(vertexAttrib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(normalAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glEnableVertexAttribArray(textureAttrib);
	//glBindBuffer(GL_ARRAY_BUFFER, textureBuffer); //todo: finish this
		//glVertexAttribPointer(textureAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, mesh->triangles.size()*3, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vertexAttrib);
	glDisableVertexAttribArray(normalAttrib);
	glDisableVertexAttribArray(textureAttrib);
}



std::shared_ptr<Mesh> RenderableObject::getMesh() const
{
	return mesh;
}
