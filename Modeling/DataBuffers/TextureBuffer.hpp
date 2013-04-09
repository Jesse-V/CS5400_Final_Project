
#ifndef TEXTURE_BUFFER
#define TEXTURE_BUFFER

#include "DataBuffer.hpp"

class TextureBuffer: public DataBuffer
{
	public:
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

	private:
		GLint textureAttrib;
		GLuint texture, buffer, vTexCoord;
};

#endif
