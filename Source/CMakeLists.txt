cmake_minimum_required(VERSION 2.6)

project(OpenGL_program)

IF(WIN32)
    set(CMAKE_CXX_FLAGS  "-O2")
ELSE()
    set(CMAKE_CXX_FLAGS  "-g -O2 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations")
ENDIF()

include_directories(. parsers glm)
#link_directories()

add_executable(OpenGL_program
    Application.cpp
    main.cpp
    Modeling/DataBuffers/TextureBuffer.cpp
    Modeling/DataBuffers/VertexBuffer.cpp
    ShaderLoader/Program.cpp
    ShaderLoader/Shader.cpp
    Modeling/Mesh.cpp
    World/Scene.cpp
    World/Camera.cpp
    World/Light.cpp
    Modeling/RenderableObject.cpp
    CustomObjects/Ground/Ground.cpp
    CustomObjects/SierpinskiMountain/SierpMountain.cpp
    CustomObjects/Mandelbrot/Mandelbrot.cpp
)

IF(WIN32)
    target_link_libraries(OpenGL_program glut glew32 GL)
ELSE()
    target_link_libraries(OpenGL_program glut GLEW GL)
ENDIF()


