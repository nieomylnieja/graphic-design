#ifndef GRAPHIC_DESIGN_SHADER_H
#define GRAPHIC_DESIGN_SHADER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

enum ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
};

class Shader {
private:
    ShaderType m_Type;
    std::string m_Filepath;
    unsigned int m_ID;

    std::string parse(const std::string &filepath);
    unsigned int compile(const std::string &source);
    static std::string getShaderTypeString(ShaderType type);
    static int getShaderTypeGLEnum(ShaderType type);

public:
    explicit Shader(const std::string &filepath);
    ~Shader();
    void Attach(unsigned int shaderProgram) const;
    void Detach(unsigned int shaderProgram) const;
    void Delete() const;
};

#endif