Final Project for CS5400: Computer Graphics
======================

This project renders the Mandelbrot fractal on a 3D spiral, and adds per-fragment lighting.

To run, type "cmake ." and then run "make" to compile. Run the produced executable.

Movement of the camera is controlled via the WASD keys, with Q and E for moving in the Z plane.
Panning of the camera is controlled via the arrow keys, and Page Up and Page Down rolls the camera.

This project relies on GLM library for OpenGL mathematics, and cmake for generating platform-independent compilation instruction. Also thanks for Shawn Badger, for helping me develop an initial C++ framework for doing OpenGL in an organized fashion.

If you do not have GLM or cmake installed, these libraries can be installed in Mint/Ubuntu with the following command:
sudo apt-get install libglm-dev cmake make

As a side note, this project was forked into https://github.com/Jesse-V/OpenGL_Texture_Mapping for a different assignment, the framework was heavily refactored, and it was merged back into this repo.
