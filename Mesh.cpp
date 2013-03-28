
#include "Mesh.hpp"


Mesh::Mesh()
{
	/*
	GLfloat triangle_vertices[] = {
		0.0,  0.8,
		-0.8, -0.8,
		0.8, -0.8,
	};

	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(
		attribute_coord2d, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		triangle_vertices  // pointer to the C array
	);*/

	generateMesh();
	storePoints();
	storeMesh();

	auto err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::ostringstream oss;
		oss << "Could not create mesh: " << err << std::endl;
		throw std::runtime_error(oss.str());
	}
}



void Mesh::render(const Camera& camera, const Point& location)
{
	glUseProgram(program->getHandle());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	auto coord3d = glGetAttribLocation(program->getHandle(), "coord3d");
	glEnableVertexAttribArray(coord3d);
	glVertexAttribPointer(coord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, m_mesh[level].size() * 3, GL_UNSIGNED_INT, 0);


	/*glUseProgram(program->getHandle());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// Setup vertex data
	glEnableVertexAttribArray(coord3d);

	auto coord3d = glGetAttribLocation(program->getHandle(), "coord3d");
	glEnableVertexAttribArray(coord3d);
	glVertexAttribPointer(coord3d,3,GL_FLOAT,GL_FALSE,0,0);

	glDrawElements(GL_TRIANGLES,m_mesh[level].size()*3,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(coord3d);



	// Push each element in buffer_vertices to the vertex shader
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(attribute_coord2d);



	glUseProgram(m_program->getHandle());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_glIndecies[level]);
	glBindBuffer(GL_ARRAY_BUFFER,m_glPoints);
	auto coord3d = glGetAttribLocation(m_program->getHandle(),"coord3d");
	glEnableVertexAttribArray(coord3d);
	glVertexAttribPointer(coord3d,3,GL_FLOAT,GL_FALSE,0,0);
	glDrawElements(GL_TRIANGLES,m_mesh[level].size()*3,GL_UNSIGNED_INT,0);*/
}



std::std::vector<GLfloat> getPoints()
{
	std::vector<GLfloat> rawPoints;
	rawPoints.reserve(m_points.size() * 3);
	std::for_each(m_points.begin(), m_points.end(),
		[&](cs5400::Point& p)
	{
		rawPoints.push_back(p.x);
		rawPoints.push_back(p.y);
		rawPoints.push_back(p.z);
	});
}



void Gasket::storePoints()
{
	std::vector<GLfloat> rawPoints = getPoints();
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawPoints.size() * sizeof(GLfloat), rawPoints.data(), GL_STATIC_DRAW);
}



void Gasket::storeMesh()
{
	glGenBuffers(1, &indexBuffer);
	std::vector<GLuint> rawIndex;
	std::for_each(m_mesh[i].begin(), m_mesh[i].end(),
		[&](Triangle tri)
	{
		rawIndex.push_back(tri.a);
		rawIndex.push_back(tri.b);
		rawIndex.push_back(tri.c);
	});

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndex.size() * sizeof(GLuint), rawIndex.data(), GL_STATIC_DRAW);
}



/*

void Model::bindVertices()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::cout << "vao: " << vao << std::endl;
}



void Model::storeVertices(std::vector<Point> vertices)
{
	vertexCount = vertices.size();
	int memSize = vertexCount * sizeof(Point);

	GLuint buffer; //pointer to the GPU memory
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, memSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, memSize, vertices.data()); //save vertices

	std::cout << "buffer: " << buffer << std::endl;
}



void Model::initializeProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	program = initShader(vertexShader.c_str(), fragmentShader.c_str());
	glUseProgram(program);
	initVertexPositionAttribute(program);
}



void Model::initVertexPositionAttribute(const GLuint& prog)
{
	GLuint vertPosition = glGetAttribLocation(prog, "vertPosition");
	glEnableVertexAttribArray(vertPosition);
	glVertexAttribPointer(vertPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}



int Model::getVertexCount()
{
	return vertexCount;
}
*/
