
#include "MandelModel.hpp"
#include <iostream>

MandelModel::MandelModel(int resolution):
	resolution(resolution)
{
	storeVertices(getVertices());
	initializeProgram();
}



/* Returns the vertices that describe the on-screen shapes */
std::vector<Point> MandelModel::getVertices()
{
	Point a(0, 0, 0);
	Point b(1, 1, 0);

	std::vector<Point> vertices;

	for (float x = 0; x < resolution; x++)
	{
		for (float y = 0; y < resolution; y++)
		{
			float xCoord = (x / resolution) * (b.x - a.x);
			float yCoord = (y / resolution) * (b.y - a.y);
			Point pt(xCoord, yCoord, 0);
			vertices.push_back(pt);
		}
	}

	return vertices;
}
