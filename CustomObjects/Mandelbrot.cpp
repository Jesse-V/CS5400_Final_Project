
#include "Mandelbrot.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"


std::vector<std::shared_ptr<DataBuffer>> Mandelbrot::getDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);
}



std::shared_ptr<Mesh> Mandelbrot::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	addVertices(mesh);
	addIndices(mesh);
	mesh->calcNormalsMWE();

	return mesh;
}



void Mandelbrot::addVertices(std::shared_ptr<Mesh>& mesh)
{
	mesh->vertices.push_back(glm::vec3(0, 1, 0.2));
	mesh->vertices.push_back(glm::vec3(0, 0, 0.2));
	mesh->vertices.push_back(glm::vec3(1, 0, 0.2));
	mesh->vertices.push_back(glm::vec3(1, 1, 0.2));
}



void Mandelbrot::addIndices(std::shared_ptr<Mesh>& mesh)
{
	mesh->triangles.push_back(Triangle(0, 1, 2));
	mesh->triangles.push_back(Triangle(0, 2, 3));
}
