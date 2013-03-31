
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
	glGenBuffers(1, &buffer);

	vertexAttrib = glGetAttribLocation(program, "vertex");
	normalAttrib = glGetAttribLocation(program, "vertexNormal");
	textureAttrib = glGetAttribLocation(program, "textureCoord");
	vTexCoord = glGetAttribLocation(program, "vTexCoord");

	glGenTextures(1, &texture);
	glUniform1i(glGetUniformLocation(program, "texture"), 0);

	storePoints();
	storeNormals();
	storeMesh();
	storeTexture();
}



// Store the vertices in a GPU buffer
void RenderableObject::storePoints()
{
	const std::vector<glm::vec3> &verts = mesh->vertices;

	std::vector<GLfloat> rawPoints;
	for_each (verts.begin(), verts.end(),
		[&](const glm::vec3& vert)
		{
			rawPoints.push_back(vert.x);
			rawPoints.push_back(vert.y);
			rawPoints.push_back(vert.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawPoints.size() * sizeof(GLfloat), rawPoints.data(), GL_STATIC_DRAW);
}



// Store the normals in a GPU buffer
void RenderableObject::storeNormals()
{
	std::vector<GLfloat> rawNormals;
	for_each (mesh->normals.begin(), mesh->normals.end(),
		[&](const glm::vec3& norm)
		{
			rawNormals.push_back(norm.x);
			rawNormals.push_back(norm.y);
			rawNormals.push_back(norm.z);
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



// Send the texture to the GPU
void RenderableObject::storeTexture()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->tex_coords), mesh->tex_coords, GL_STATIC_DRAW);
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

		enableVertices();
		enableNormals();
		enableTexture();

		glDrawElements(GL_TRIANGLES, mesh->triangles.size() * 3, GL_UNSIGNED_INT, 0);

		finalizeRendering();
	}
}



void RenderableObject::enableVertices()
{
	glEnableVertexAttribArray(vertexAttrib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}



void RenderableObject::enableNormals()
{
	glEnableVertexAttribArray(normalAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}



void RenderableObject::enableTexture()
{
	glEnableVertexAttribArray(vTexCoord);
	glBindTexture(GL_TEXTURE_2D, texture);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glActiveTexture(GL_TEXTURE0);
}



void RenderableObject::finalizeRendering()
{
	glDisableVertexAttribArray(vertexAttrib);
	glDisableVertexAttribArray(normalAttrib);
	glDisableVertexAttribArray(textureAttrib);
	glDisableVertexAttribArray(vTexCoord);
}



std::shared_ptr<Mesh> RenderableObject::getMesh() const
{
	return mesh;
}
