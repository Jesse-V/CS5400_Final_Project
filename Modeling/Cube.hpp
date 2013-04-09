
#ifndef CUBE_HPP
#define CUBE_HPP

#include "Mesh.hpp"
#include <memory>

class Cube
{
	public:
		std::vector<DataBuffer> getDataBuffers();

	private:
		std::shared_ptr<Mesh> getMesh();
		TextureBuffer getTexture();
		void addVertices(std::shared_ptr<Mesh>& mesh);
		void addIndices(std::shared_ptr<Mesh>& mesh);
		//void quad(int a, int b, int c, int d, int& index, std::shared_ptr<Mesh>& mesh);
};

#endif
