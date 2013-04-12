
#include "Ground.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"
#include <iostream>


std::vector<std::shared_ptr<DataBuffer>> Ground::getDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);

	return buffers;
}



std::shared_ptr<Mesh> Ground::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	std::cout << "Assembling Ground Model (4), making... ";

	std::cout << "vertices... ";
	addVertices(mesh);

	std::cout << "triangles... ";
	addIndices(mesh);

	std::cout << "normals... ";
	mesh->calcNormalsMWE();

	std::cout << "done" << std::endl;
	return mesh;
}



void Ground::addVertices(std::shared_ptr<Mesh>& mesh)
{
	mesh->vertices.push_back(glm::vec3(	1, 0, -1));
	mesh->vertices.push_back(glm::vec3(-1, 0, -1));
	mesh->vertices.push_back(glm::vec3(-1, 0,  1));
	mesh->vertices.push_back(glm::vec3(	1, 0,  1));
}



void Ground::addIndices(std::shared_ptr<Mesh>& mesh)
{
	mesh->triangles.push_back(Triangle(0, 1, 2));
	mesh->triangles.push_back(Triangle(0, 2, 3));
}
