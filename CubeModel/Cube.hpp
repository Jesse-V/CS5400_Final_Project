#ifndef GROUND_MODEL_HPP
#define GROUND_MODEL_HPP

#include "../Model.hpp"

class GroundModel: public Model
{
	public:
		GroundModel(int resolution);
		std::vector<Point> getVertices();

	private:
		int resolution;
};

#endif
