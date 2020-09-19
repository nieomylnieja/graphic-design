#include <glad/glad.h>
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <spdlog/spdlog.h>

Shader::Shader(const std::string &filepath)
        : m_Filepath(filepath), m_ID(0), m_Type(NONE) {
    std::string source = parse(filepath);
    m_ID = compile(source);
}

Shader::~Shader() {
    glDeleteShader(m_ID);
}

void Shader::Attach(unsigned int shaderProgram) const {
    glAttachShader(shaderProgram, m_ID);
}

void Shader::Detach(unsigned int shaderProgram) const {
    glDetachShader(shaderProgram, m_ID);
}

void Shader::Delete() const {
    glDeleteShader(m_ID);
}

unsigned int Shader::compile(const std::string &source) {
    unsigned int id = glCreateShader(getShaderTypeGLEnum(m_Type));
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        spdlog::error("Failed to compile {} shader. Message: {}", getShaderTypeString(m_Type), message);
        glDeleteShader(id);
    }
    return id;
}

std::string Shader::parse(const std::string &filepath) {
    std::ifstream stream(filepath);
    if (stream.fail() || stream.bad()) {
        spdlog::error("failed to open the file: {}", filepath);
        exit(1);
    }

    std::string line;
    std::stringstream ss;
    while (getline(stream, line)) {
        if (boost::contains(line, "#type")) {
            std::vector<std::string> split;
            boost::split(split, line, boost::is_any_of("\t "));
            if (split.size() != 2) {
                spdlog::error("invalid header specification, please provide the shader type as such: '#type vertex'");
            }
            if (split[1] == "vertex") {
                m_Type = VERTEX;
            } else if (split[1] == "fragment") {
                m_Type = FRAGMENT;
            } else if (split[1] == "geometry") {
                m_Type = GEOMETRY;
            }
            continue;
        }
        ss << line << '\n';
    }
    return ss.str();
}

std::string Shader::getShaderTypeString(ShaderType type) {
    switch (type) {
        case NONE:
            spdlog::error("shader type was not initialized and is set to NONE");
            exit(1);
        case VERTEX:
            return "vertex";
        case FRAGMENT:
            return "fragment";
        case GEOMETRY:
            return "geometry";
        default:
            spdlog::error("shader type was not initialized at all");
            exit(1);
    }
}

int Shader::getShaderTypeGLEnum(ShaderType type) {
    switch (type) {
        case NONE:
            spdlog::error("shader type was not initialized and is set to NONE");
            exit(1);
        case VERTEX:
            return GL_VERTEX_SHADER;
        case FRAGMENT:
            return GL_FRAGMENT_SHADER;
        case GEOMETRY:
            return GL_GEOMETRY_SHADER;
        default:
            spdlog::error("shader type was not initialized at all");
            exit(1);
    }
}
