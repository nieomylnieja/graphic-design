#ifndef GRAPHIC_DESIGN_MESH_H
#define GRAPHIC_DESIGN_MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "texture.h"
#include "shader_program.h"
#include "element_buffer.h"
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "material.h"

class Mesh {
public:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;

    Material m_Material;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material &material);
    ~Mesh();

    void Draw(ShaderProgram &shaderProgram);
private:
    bool m_IsMaterial;

    unsigned int vaox{};
    VertexArray vao{};
    VertexBuffer vbo{};
    ElementBuffer ebo{};

    void setupMesh();

    void drawTexture(ShaderProgram &shaderProgram);
    void drawMaterial(ShaderProgram &shaderProgram);
};

#endif