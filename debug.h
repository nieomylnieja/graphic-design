#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// sigtrap should work for most posix compilers
#define ASSERT(x) if (!(x)) raise(SIGTRAP);

void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);
