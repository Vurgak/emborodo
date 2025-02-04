#pragma once

#include <enborodo/utilities/noncopyable.hpp>

#include <glm/vec3.hpp>

namespace em
{

class game_object : public en::noncopyable
{
public:
    virtual ~game_object() = default;

    glm::vec3 position;
};

}
