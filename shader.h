#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
private:
    std::string m_Filepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

    static ShaderProgramSource parse(const std::string &filepath);

    int getUniformLocation(const std::string &name);

    static unsigned int compile(unsigned int type, const std::string &source);

    static unsigned int create(const std::string &vertexShader, const std::string &fragmentShader);

public:
    explicit Shader(const std::string &filepath);

    ~Shader();

    void Bind() const;

    static void Unbind();

    // Set uniforms
    void SenUniform4f(const std::string &name, const std::vector<float> &v);
};
