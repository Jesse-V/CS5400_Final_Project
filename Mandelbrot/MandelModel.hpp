#ifndef MANDEL_MODEL_HPP
#define MANDEL_MODEL_HPP

#include "../Model.hpp"

class MandelModel: public Model
{
	public:
		MandelModel(int resolution);
		std::vector<Point> getVertices();

	private:
		int resolution;
};

#endif
