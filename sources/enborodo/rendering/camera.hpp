#pragma once

#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API camera
{
public:
    virtual ~camera() = default;

    virtual void set_position(glm::vec3 position) = 0;

    virtual void look_at(glm::vec3 target) = 0;

    virtual const glm::mat4& get_view() = 0;

    virtual const glm::mat4& get_projection() = 0;
};

using camera_ptr = std::unique_ptr<camera>;

}
