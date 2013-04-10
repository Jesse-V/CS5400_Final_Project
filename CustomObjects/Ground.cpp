
#include "Ground.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"


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

	addVertices(mesh);
	addIndices(mesh);
	mesh->calcNormalsMWE();

	return mesh;
}



void Ground::addVertices(std::shared_ptr<Mesh>& mesh)
{
	mesh->vertices.push_back(glm::vec3(60, -0.2, -60));
	mesh->vertices.push_back(glm::vec3(-60, -0.2, -60));
	mesh->vertices.push_back(glm::vec3(-60, -0.2, 60));
	mesh->vertices.push_back(glm::vec3(60, -0.2, 60));
}



void Ground::addIndices(std::shared_ptr<Mesh>& mesh)
{
	mesh->triangles.push_back(Triangle(0, 1, 2));
	mesh->triangles.push_back(Triangle(0, 2, 3));
}
