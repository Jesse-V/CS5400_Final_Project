
#include "GroundModel.hpp"
#include <iostream>

GroundModel::GroundModel(int modelResolution):
	resolution(modelResolution)
{
	bindVertices();
	storeVertices(getVertices());
	initializeProgram("Ground/vertex.glsl", "Ground/fragment.glsl");
}



/* Returns the vertices that describe the on-screen shapes */
std::vector<Point> GroundModel::getVertices()
{
	int zCoord = 0.2;
	Point a(0.2, 0.2, zCoord);
	Point b(1.2, 1.2, zCoord);

	std::vector<Point> vertices;

	for (float x = 0; x < resolution; x++)
	{
		for (float y = 0; y < resolution; y++)
		{
			float xCoord = (x / resolution) * (b.x - a.x);
			float yCoord = (y / resolution) * (b.y - a.y);
			Point pt(xCoord, yCoord, zCoord);
			vertices.push_back(pt);
		}
	}

	return vertices;
}
