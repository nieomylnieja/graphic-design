#pragma once

#include "shader.h"

class ShaderProgram {
private:
    unsigned int m_ID;

    void linkProgram() const;

public:
    explicit ShaderProgram(const std::vector<Shader> &shaders);
    ~ShaderProgram();
    void Bind() const;
    static void Unbind();
    unsigned int GetID() const { return m_ID; };
};
