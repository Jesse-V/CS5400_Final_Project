
#ifndef CUBE_HPP
#define CUBE_HPP

#include "Modeling/Mesh.hpp"
#include "Modeling/DataBuffers/TextureBuffer.hpp"
#include <memory>

class Cube
{
	public:
		std::vector<std::shared_ptr<DataBuffer>> getDataBuffers();

	private:
		std::shared_ptr<Mesh> getMesh();
		std::shared_ptr<TextureBuffer> getTextureBuffer();
		void addVertices(std::shared_ptr<Mesh>& mesh);
		void addIndices(std::shared_ptr<Mesh>& mesh);
		//void quad(int a, int b, int c, int d, int& index, std::shared_ptr<Mesh>& mesh);
};

#endif
