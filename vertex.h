#ifndef GRAPHIC_DESIGN_VERTEX_H
#define GRAPHIC_DESIGN_VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

#endif //GRAPHIC_DESIGN_VERTEX_H
