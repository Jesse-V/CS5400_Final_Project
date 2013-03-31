
#include "Cube.hpp"


std::shared_ptr<Mesh> Cube::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	setVertices(mesh);
	setIndices(mesh);
	setTexture(mesh);
	mesh->calcNormalsMWE();

	return mesh;
}



//make a cube, centered at the origin, sides aligned with axes
void Cube::setVertices(std::shared_ptr<Mesh>& mesh)
{
	mesh->vertices.push_back(glm::vec3(-0.5, -0.5,  0.5));
	mesh->vertices.push_back(glm::vec3(-0.5,  0.5,  0.5));
	mesh->vertices.push_back(glm::vec3( 0.5,  0.5,  0.5));
	mesh->vertices.push_back(glm::vec3( 0.5, -0.5,  0.5));
	mesh->vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
	mesh->vertices.push_back(glm::vec3(-0.5,  0.5, -0.5));
	mesh->vertices.push_back(glm::vec3( 0.5,  0.5, -0.5));
	mesh->vertices.push_back(glm::vec3( 0.5, -0.5, -0.5));
}



void Cube::setIndices(std::shared_ptr<Mesh>& mesh)
{
	int indices[36];

	//front side
	indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
	indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

	//Back side
	indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
	indices[9]  = 4; indices[10] = 7; indices[11] = 6;

	//Left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	//Right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	//top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	//bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	for (int j = 0; j < 36; j += 3)
		mesh->triangles.push_back(Triangle(indices[j], indices[j + 1], indices[j + 2]));
}



void Cube::setTexture(std::shared_ptr<Mesh>& mesh)
{
	for (int j = 0; j < 12; j++)
	{
		mesh->textureMap.push_back(glm::vec2(0, 0));
		mesh->textureMap.push_back(glm::vec2(0, 1));
		mesh->textureMap.push_back(glm::vec2(1, 1));
		mesh->textureMap.push_back(glm::vec2(1, 0));
	}
}
