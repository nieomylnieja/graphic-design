#include <glad/glad.h>
#include "mesh.h"

#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    m_Vertices = std::move(vertices);
    m_Indices = std::move(indices);
    m_Textures = std::move(textures);

    setupMesh();
}

Mesh::~Mesh() = default;

void Mesh::Draw(ShaderProgram &shaderProgram) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < m_Textures.size(); i++) {
        m_Textures[i].Bind(i);
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string type = m_Textures[i].GetType();
        if (type == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (type == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (type == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (type == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream
        // now set the sampler to the correct texture unit
        shaderProgram.SetUniform(type + number, i);
        // and finally bind the texture
        m_Textures[i].Unbind();
    }

    // draw mesh
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

// TODO use vertex_buffer and the family here
void Mesh::setupMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}
