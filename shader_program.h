#ifndef GRAPHIC_DESIGN_SHADER_PROGRAM_H
#define GRAPHIC_DESIGN_SHADER_PROGRAM_H

#include "shader.h"

class ShaderProgram {
private:
    unsigned int m_ID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

    void linkProgram() const;

    int getUniformLocation(const std::string &name);

    template<typename T>
    static void SetUniform(int loc, T v) { static_assert(true, ""); }
    static void SetUniform(int loc, int v);
    static void SetUniform(int loc, const std::vector<float> &v);
    static void SetUniform(int loc, glm::mat4 v);

public:
    explicit ShaderProgram(const std::vector<Shader> &shaders);
    ~ShaderProgram();
    void Use() const;
    static void Unbind();
    unsigned int GetID() const { return m_ID; };

    template<typename T>
    void SetUniform(const std::string &name, T v) {
        SetUniform(getUniformLocation(name), v);
    };
};

#endif