
#ifndef MANDELBROT_OBJECT
#define MANDELBROT_OBJECT

#include "CustomObject.hpp"

class Mandelbrot: public CustomObject
{
	public:
		virtual std::vector<std::shared_ptr<DataBuffer>> getDataBuffers();

	protected:
		virtual std::shared_ptr<Mesh> getMesh();
		virtual void addVertices(std::shared_ptr<Mesh>& mesh);
		virtual void addIndices(std::shared_ptr<Mesh>& mesh);

	private:
		const float PI = 3.1415926535897932384626433832795f;
		const int RESOLUTION = 1024; //1024 is good resolution
};

#endif
