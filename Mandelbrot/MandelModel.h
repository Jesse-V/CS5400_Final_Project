#ifndef MANDEL_MODEL_HPP
#define MANDEL_MODEL_HPP

#include "Model.h"

class MandelModel: public Model
{
	public:
		virtual std::vector<Point> getVertices();
}