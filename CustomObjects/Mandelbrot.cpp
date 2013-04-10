
#include "Mandelbrot.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"
#include <cmath>
#include <iostream>


std::vector<std::shared_ptr<DataBuffer>> Mandelbrot::getDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);

	return buffers;
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
	for (float height = 0; height <= RESOLUTION; height++)
	{
		float theta = (2 * 2 * PI) * (height / RESOLUTION);

		float x = (float)sin(theta) * (theta * 0.02f);
		float y = (float)cos(theta) * (theta * 0.02f);

		for (float width = 0; width <= RESOLUTION; width++)
		{
			float z = 1 * (width / RESOLUTION);

			//std::cout << theta << ": " << x << ", " << y << ", " << z << std::endl;
			mesh->vertices.push_back(glm::vec3(x, y, z));
		}
	}
}



void Mandelbrot::addIndices(std::shared_ptr<Mesh>& mesh)
{
	for (int x = 0; x < RESOLUTION * RESOLUTION - RESOLUTION - 1; x++)
	{
		//if (x % RESOLUTION != RESOLUTION - 1)
		{
			int y = x + 1;

			int z0 = x + RESOLUTION;
			int z1 = z0 + 1;

			//std::cout << (x % RESOLUTION) << std::endl;
			//std::cout << x << ", " << y << ", " << z0 << std::endl;
			//std::cout << x << ", " << y << ", " << z1 << std::endl;
			//std::cout << std::endl;

			mesh->triangles.push_back(Triangle(x, y, z0));
			mesh->triangles.push_back(Triangle(y, z1, z0));
		}
	}
}
