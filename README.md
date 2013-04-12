Final Project for CS5400: Computer Graphics
======================

This project renders the Mandelbrot fractal on a 3D spiral, and adds per-fragment lighting.

To run, first make sure you have the required dependencies installed (see below). Then run "cmake .", and a makefile will be generated. Run "make" to compile. Finally, run the produced executable with "./OpenGL_program".

Movement of the camera is controlled via the WASD keys, with Q and E for moving vertically.
Panning of the camera is controlled via the arrow keys, and Page Up and Page Down rolls the camera.

This code relies on the GLEW and Freeglut libraries to create the window and use OpenGL, the GLM library for OpenGL mathematics, and cmake for generating platform-independent compilation instructions (such as makefiles). The build-essential package is needed for linking cmake to the compiler. Shawn Badger's organized code was very helpful when I first developing this C++/OpenGL framework.

If you do not have Glew, Freeglut, GLM, cmake, or build-essential installed, these libraries can be installed from the Mint/Ubuntu repos with the following command:
sudo apt-get install libglew-dev freeglut3-dev libglm-dev cmake build-essential

This project coded exclusively in Linux Mint, and was initially forked into https://github.com/Jesse-V/OpenGL_Texture_Mapping for a different assignment, the framework was heavily refactored, and then it was merged back into this repo for further development.
