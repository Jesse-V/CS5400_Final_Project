
#include "MandelModel.h"

/* Returns the vertices that describe the on-screen shapes */
std::vector<Point> MandelModel::getVertices()
{
	Point a(0, 0, 0);
	Point b(1, 1, 0);

	std::vector<Point> vertices;

	for (float x = 0; x < res; x++)
	{
		for (float y = 0; y < res; y++)
		{
			float xCoord = (x / res) * (b.x - a.x);
			float yCoord = (y / res) * (b.y - a.y);
			Point pt(xCoord, yCoord, 0);
			vertices.push_back(pt);
		}
	}

	std::cout << "Coord count: " << vertices.size() << std::endl;
	return vertices;
}