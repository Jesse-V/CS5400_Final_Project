cmake_minimum_required(VERSION 2.6)

project(render)

IF(WIN32)
    set(CMAKE_CXX_FLAGS  "-O2")
ELSE()
    set(CMAKE_CXX_FLAGS  "-g -O2 --std=c++0x -Wall")
ENDIF()

include_directories(. parsers glm)
#link_directories()

add_executable(render
    main.cpp
    ShaderLoader/Program.cpp
    ShaderLoader/Shader.cpp
    Util.cpp
    Modeling/Mesh.cpp
    Scene.cpp
    Camera.cpp
    Modeling/RenderedObject.cpp
    Modeling/Cube.cpp
)

IF(WIN32)
    target_link_libraries(render glut glew32 GL)
ELSE()
    target_link_libraries(render glut GLEW GL)
ENDIF()


