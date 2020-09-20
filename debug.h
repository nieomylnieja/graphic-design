#ifndef GRAPHIC_DESIGN_DEBUG_H
#define GRAPHIC_DESIGN_DEBUG_H

//#include <GL/glew.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);

#endif