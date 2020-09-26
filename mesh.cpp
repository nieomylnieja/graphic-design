#include <glad/glad.h>
#include "mesh.h"

#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
        : m_IsMaterial(false) {
    m_Vertices = std::move(vertices);
    m_Indices = std::move(indices);
    m_Textures = std::move(textures);

    setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material &material) : m_IsMaterial(true) {
    m_Vertices = std::move(vertices);
    m_Indices = std::move(indices);
    m_Material = material;

    setupMesh();
}

Mesh::~Mesh() = default;

void Mesh::Draw(ShaderProgram &shaderProgram) {
    if (m_IsMaterial) {
        drawMaterial(shaderProgram);
    } else {
        drawTexture(shaderProgram);
    }
}

void Mesh::drawTexture(ShaderProgram &shaderProgram) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < m_Textures.size(); i++) {
        m_Textures[i].Bind(i);
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string type = m_Textures[i].GetType();
        if (type == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (type == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (type == "texture_ambient") {
            number = std::to_string(normalNr++);
        } else if (type == "texture_height") {
            number = std::to_string(heightNr++);
        }
        // now set the sampler to the correct texture unit
        shaderProgram.SetUniform(type + number, i);
    }

    // draw mesh
    vao.Bind();
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    VertexArray::Unbind();
    Texture::Unbind();
}

void Mesh::drawMaterial(ShaderProgram &shaderProgram) {
    shaderProgram.SetUniform("material.diffuse", m_Material.Diffuse);
    shaderProgram.SetUniform("material.specular", m_Material.Specular);
    shaderProgram.SetUniform("material.ambient", m_Material.Ambient);
    shaderProgram.SetUniform("material.shininess", m_Material.Shininess);

    // draw mesh
    vao.Bind();
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    VertexArray::Unbind();
}

// TODO use vertex_buffer and the family here
void Mesh::setupMesh() {
    VertexArray vaoDecl = VertexArray();
    vao = vaoDecl;
    vao.Bind();

    VertexBuffer vboDecl = VertexBuffer(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));
    vbo = vboDecl;

    ElementBuffer eboDecl = ElementBuffer(&m_Indices[0], m_Indices.size());
    ebo = eboDecl;

    VertexBufferLayout layout = VertexBufferLayout();
    layout.Push<Vertex>(3);
    layout.Push<Vertex>(3, offsetof(Vertex, Normal));
    layout.Push<Vertex>(2, offsetof(Vertex, TexCoords));
    layout.Push<Vertex>(3, offsetof(Vertex, Tangent));
    layout.Push<Vertex>(3, offsetof(Vertex, Bitangent));
    layout.SetStride(sizeof(Vertex));
    vao.AddBuffer(vbo, layout);

    VertexArray::Unbind();
}
