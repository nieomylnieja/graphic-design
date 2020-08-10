cmake_minimum_required(VERSION 3.15)
project(graphic_design)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED)
find_package (glm REQUIRED)
find_package (GLEW REQUIRED STATIC)

set(SOURCE_FILES main.cpp debug.h debug.cpp index_buffer.cpp index_buffer.h vertex_buffer.cpp vertex_buffer.h vertex_array.cpp vertex_array.h vertex_buffer_layout.h)
add_executable(graphic_design ${SOURCE_FILES})
target_link_libraries(graphic_design GL GLU GLEW glfw3 Xxf86vm pthread Xrandr Xinerama Xi X11 Xcursor)
