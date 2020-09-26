#ifndef GRAPHIC_DESIGN_MATERIAL_H
#define GRAPHIC_DESIGN_MATERIAL_H

#include <glm/glm.hpp>

struct Material {
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    glm::vec3 Ambient;
    float Shininess;
};

#endif
