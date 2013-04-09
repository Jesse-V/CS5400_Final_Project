
#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "DataBuffer.hpp"

class IndexBuffer: public DataBuffer
{
	public:
		virtual void enable();

	protected:
		virtual void getAttribute(GLuint program);
		virtual void storeBuffer();


};

#endif
