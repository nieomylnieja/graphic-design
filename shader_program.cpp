#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>
#include "shader_program.h"

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders) : m_ID(glCreateProgram()) {
    for (const auto &shader: shaders) {
        shader.Attach(m_ID);
    }
    linkProgram();
    Use();
    for (const auto &shader: shaders) {
        shader.Delete();
    }
}

ShaderProgram::~ShaderProgram() {
    Unbind();
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

void ShaderProgram::Use() const {
    glUseProgram(m_ID);
}

void ShaderProgram::Unbind() {
    glUseProgram(0);
}


int ShaderProgram::getUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache.at(name);
    }
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1) {
        spdlog::warn("Uniform {} doesn't exist!", name);
    }
    m_UniformLocationCache.insert({name, location});
    return location;
}

void ShaderProgram::SetUniform(const int loc, int v) {
    glUniform1i(loc, v);
}

void ShaderProgram::SetUniform(const int loc, const std::vector<float> &v) {
    switch (v.size()) {
        case 4:
            glUniform4f(loc, v[0], v[1], v[2], v[3]);
            return;
        default:
            spdlog::error("undefined float vector uniform for size: {}", v.size());
            exit(1);
    }
}

void ShaderProgram::SetUniform(int loc, glm::mat4 v) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v));
}
