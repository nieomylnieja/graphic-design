cmake_minimum_required(VERSION 3.18.2)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/lib/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
project(graphic_design)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3 lib/vcpkg/packages)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(Assimp CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(SOURCE_FILES main.cpp debug.h debug.cpp vertex_buffer.h vertex_buffer.cpp shader.h shader.cpp shader_program.cpp
        shader_program.h element_buffer.h element_buffer.cpp vertex_buffer_layout.h vertex_array.h vertex_array.cpp identity.h renderer.cpp
        texture.h texture.cpp camera.cpp camera.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} GL GLU GLEW glfw3 Xxf86vm pthread Xrandr Xinerama Xi X11 Xcursor glad::glad assimp::assimp)

add_subdirectory(lib/spdlog)

target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
