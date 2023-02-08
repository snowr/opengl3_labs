cmake_minimum_required(VERSION 3.24)
project(opengl3_labs)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(opengl3_labs main.cpp GL/glew.h GL/glxew.h GL/wglew.h)
target_link_libraries(opengl3_labs GLEW GLU glut GL glfw ${CMAKE_SOURCE_DIR}/libs/libsoil.a)
