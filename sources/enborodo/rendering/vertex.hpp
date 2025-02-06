#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace en
{

struct vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coord;
};

}
