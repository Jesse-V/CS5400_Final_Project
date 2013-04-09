
#ifndef GROUND_OBJECT
#define GROUND_OBJECT

#include "CustomObject.hpp"

class Ground: public CustomObject
{
	public:
		virtual std::vector<std::shared_ptr<DataBuffer>> getDataBuffers();

	protected:
		virtual std::shared_ptr<Mesh> getMesh();
		virtual void addVertices(std::shared_ptr<Mesh>& mesh);
		virtual void addIndices(std::shared_ptr<Mesh>& mesh);
};

#endif
