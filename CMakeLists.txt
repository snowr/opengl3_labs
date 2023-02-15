cmake_minimum_required(VERSION 3.24)
project(opengl3_labs)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${CMAKE_SOURCE_DIR}/imgui
        ${CMAKE_SOURCE_DIR}/imgui/backends
)

# Create library
add_library(imguilib STATIC
        ${CMAKE_SOURCE_DIR}/imgui/imgui.h
        ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
        ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
        )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(opengl3_labs main.cpp GL/glew.h GL/glxew.h GL/wglew.h imgui_utils.h)
target_link_libraries(opengl3_labs imguilib GLEW GLU glut GL glfw ${CMAKE_SOURCE_DIR}/libs/libsoil.a)
