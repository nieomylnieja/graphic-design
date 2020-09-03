#include <GL/glew.h>
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

int Shader::getUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache.at(name);
    }
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    m_UniformLocationCache.insert({name, location});
    return location;
}

Shader::Shader(const std::string &filepath)
        : m_Filepath(filepath), m_RendererID(0) {
    ShaderProgramSource source = parse(filepath);
    m_RendererID = create(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SenUniform4f(const std::string &name, const std::vector<float> &v) {
    glUniform4f(getUniformLocation(name), v[0], v[1], v[2], v[4]);
}

ShaderProgramSource Shader::parse(const std::string &filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
            continue;
        }
        ss[(int) type] << line << '\n';
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compile(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
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
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader"
                  << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }
    return id;
}

unsigned int Shader::create(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compile(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
