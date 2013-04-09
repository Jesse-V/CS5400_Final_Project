
#include "DataBuffer.hpp"


DataBuffer::DataBuffer()
{

}



void DataBuffer::initialize(GLuint program)
{
	getAttribute(program);
	storeBuffer();
}



void DataBuffer::disable()
{
	glDisableVertexAttribArray(attribute);
}
