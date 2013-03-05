CC=g++
CPPFLAGS=--std=c++0x -g3 -pedantic -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations
LDLIBS=-lglut -lGLEW -lGLEW -lGL
all: Main; ./Main; make clean
Main: World.o Mandelbrot/MandelModel.o Ground/GroundModel.o Model.o ShaderLoader.o
clean:
	rm -f *.o */*.o Main
.PHONY: all clean
