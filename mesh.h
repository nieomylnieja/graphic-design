#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "texture.h"
#include "shader_program.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

class Mesh {
public:
    unsigned int vao{};
    // mesh data
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();

    void Draw(ShaderProgram &shaderProgram);
private:
    //  render data
    unsigned int vbo{}, ebo{};

    void setupMesh();
};
