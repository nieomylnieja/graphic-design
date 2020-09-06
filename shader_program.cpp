#include <spdlog/spdlog.h>
#include "shader_program.h"
#include "lib/glad/glad.h"

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders) : m_ID(glCreateProgram()) {
    for (const auto &shader: shaders) {
        shader.Attach(m_ID);
    }
    linkProgram();
    glUseProgram(m_ID);
    for (const auto &shader: shaders) {
        shader.Delete();
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ID);
}

void ShaderProgram::linkProgram() const {
    glLinkProgram(m_ID);

    int result;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetProgramInfoLog(m_ID, length, &length, message);
        spdlog::error("Failed to link shader program. Message: {}", message);
        glDeleteProgram(m_ID);
    }
}
