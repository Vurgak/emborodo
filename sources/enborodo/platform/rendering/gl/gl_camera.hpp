#pragma once

#include <glm/mat4x4.hpp>

#include <enborodo/rendering/camera.hpp>

namespace en
{

class EN_API gl_camera final : public camera
{
public:
    gl_camera();

    void set_position(glm::vec3 position) override;

    void look_at(glm::vec3 target) override;

    const glm::mat4& get_view() override;

    const glm::mat4& get_projection() override;

private:
    bool m_dirty = false; ///< Whether the view matrix needs to be recalculated.
    glm::mat4 m_view{};

    static constexpr glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_position{};
    glm::vec3 m_target{};

    glm::mat4 m_projection{};

    static constexpr float m_fov = 45.0f;
    static constexpr float m_aspect = 16.0f / 9.0f;
    static constexpr float m_near = 0.1f;
    static constexpr float m_far = 100.0f;
};

}
