OpenGL_Texture_Mapping
======================

Texture mapping and per-fragment lighting in OpenGL.

To run, type "cmake ." and then run "make" to compile. Run the produced executable.

Movement of the camera is controlled via the WASD keys, with Q and E for moving in the Z plane.
Panning of the camera is controlled via the arrow keys, and Page Up and Page Down rolls the camera.

This project relies on GLM library for OpenGL mathematics, and cmake for generating platform-independent compilation instruction. Much of the framework was adapted from Shawn Badger, to whom I am very grateful for his skills in OpenGL and code organization.

In Mint/Ubuntu, these libraries can be installed with the following command:
sudo apt-get install libglm-dev cmake make
