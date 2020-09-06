#pragma once

#include <string>
#include <vector>
#include <unordered_map>

enum ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
};

class Shader {
private:
    ShaderType m_Type;
    std::string m_Filepath;
    unsigned int m_ID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

    std::string parse(const std::string &filepath);
    unsigned int compile(const std::string &source);
    int getUniformLocation(unsigned int program, const std::string &name);
    static std::string getShaderTypeString(ShaderType type);
    static int getShaderTypeGLEnum(ShaderType type);

    template<typename T>
    static void SetUniform(int loc, T v) { static_assert(true, ""); }
    static void SetUniform(int loc, int v);
    static void SetUniform(int loc, const std::vector<float> &v);

public:
    explicit Shader(const std::string &filepath);
    ~Shader();
    void Attach(unsigned int shaderProgram) const;
    void Detach(unsigned int shaderProgram) const;
    void Delete() const;

    template<typename T>
    void SetUniform(unsigned int program, const std::string &name, T v) {
        SetUniform(getUniformLocation(program, name), v);
    };
};
