#ifndef MANDEL_MODEL_HPP
#define MANDEL_MODEL_HPP

#include "../Model.hpp"

class MandelModel: public Model
{
	public:
		MandelModel();

		virtual std::vector<Point> getVertices();

	private:
		int res = 512;
};

#endif