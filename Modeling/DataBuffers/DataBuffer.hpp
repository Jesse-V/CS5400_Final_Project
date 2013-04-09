
#ifndef DATA_BUFFER
#define DATA_BUFFER

class DataBuffer
{
	public:
		virtual void initialize(GLuint program) = NULL;
		virtual void store() = NULL;
		virtual void enable() = NULL;
		virtual void disable() = NULL;
};

#endif
