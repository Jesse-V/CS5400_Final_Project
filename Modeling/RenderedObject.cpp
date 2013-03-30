
#include "RenderedObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <vector>
#include <algorithm>


RenderedObject::RenderedObject(GLuint program, const std::shared_ptr<Mesh>& mesh):
	_mesh(mesh), _modelmatrix(glm::mat4(1.0)), _visible(true)
{
	glGenBuffers(1, &_glvertexbuffer);
	glGenBuffers(1, &_glnormalbuffer);
	glGenBuffers(1, &_glmeshbuffer);

	_glvertexattrib = glGetAttribLocation(program, "vertex");
	_glnormalattrib = glGetAttribLocation(program, "vertexNormal");

	storePoints();
	storeNormals();
	storeMesh();
}



// Store the vertices in a GPU buffer
void RenderedObject::storePoints()
{
	const std::vector<glm::vec3> &verts = _mesh->vertices;

	std::vector<GLfloat> rawpoints;
	for_each (verts.begin(), verts.end(),
		[&](const glm::vec3& v)
		{
			rawpoints.push_back(v.x);
			rawpoints.push_back(v.y);
			rawpoints.push_back(v.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, _glvertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, rawpoints.size()*sizeof(GLfloat), rawpoints.data(), GL_STATIC_DRAW);
}



// Store the normals in a GPU buffer
void RenderedObject::storeNormals()
{
	const std::vector<glm::vec3> &normals = _mesh->normals;

	std::vector<GLfloat> rawnormals;
	for_each (normals.begin(), normals.end(),
		[&](const glm::vec3& n)
		{
			rawnormals.push_back(n.x);
			rawnormals.push_back(n.y);
			rawnormals.push_back(n.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, _glnormalbuffer);
	glBufferData(GL_ARRAY_BUFFER, rawnormals.size()*sizeof(GLfloat), rawnormals.data(), GL_STATIC_DRAW);
}



// Store the mesh in a GPU buffer
void RenderedObject::storeMesh()
{
	const std::vector<Triangle> &triangles = _mesh->triangles;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glmeshbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size()*3*sizeof(GLuint), triangles.data(), GL_STATIC_DRAW);
}



// Rotate the object along the arbitrary axis, by 'theta' degrees
void RenderedObject::rotate(const glm::vec3& axis, double theta)
{

}



// Move the object along the x, y, and z axes in the amount specified
void RenderedObject::translate(const glm::vec3& xyz)
{

}



// Objects that are not 'visible' will not be rendered
void RenderedObject::setVisible(bool visible)
{
	_visible = visible;
}



// Set the matrix to convert from model coords to world coords
void RenderedObject::setModelMatrix(const glm::mat4& matrix)
{
	_modelmatrix = matrix;
}



// Render the object
void RenderedObject::render(GLuint modelmatrixid)
{
	// Don't render if it's been flagged as not visible
	if (!_visible)
		return;

	glUniformMatrix4fv(modelmatrixid, 1, GL_FALSE, glm::value_ptr(_modelmatrix));

	glEnableVertexAttribArray(_glvertexattrib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glmeshbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _glvertexbuffer);
	glVertexAttribPointer(_glvertexattrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(_glnormalattrib);
	glBindBuffer(GL_ARRAY_BUFFER, _glnormalbuffer);
	glVertexAttribPointer(_glnormalattrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, _mesh->triangles.size()*3, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(_glvertexattrib);
	glDisableVertexAttribArray(_glnormalattrib);
}
