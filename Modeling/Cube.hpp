
#ifndef CUBE_HPP
#define CUBE_HPP

#include "Mesh.hpp"
#include <memory>

class Cube
{
	public:
		std::shared_ptr<Mesh> getMesh();

	private:
		void setVertices(std::shared_ptr<Mesh>& mesh);
		void setIndices(std::shared_ptr<Mesh>& mesh);
		void setTexture(std::shared_ptr<Mesh>& mesh);
};

#endif
