#pragma once

//#include <GL/glew.h>
#include <iostream>
//#include "lib/glad/glad.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);
