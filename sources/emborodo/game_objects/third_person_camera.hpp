#pragma once

#include <enborodo/rendering/camera.hpp>

#include <emborodo/game_objects/game_object.hpp>

namespace en
{

class input;

}

namespace em
{

class third_person_camera final : game_object
{
public:
    third_person_camera(en::camera_ptr&& camera, en::input& input);

    ~third_person_camera() override = default;

    void set_target(const game_object& target, glm::vec3 offset = glm::vec3{0.0f});

    void update();

    [[nodiscard]]
    en::camera& get_impl() const;

private:
    static constexpr float c_camera_sensitivity = 0.2f;
    static constexpr float c_zoom_sensitivity = 0.5f;
    static constexpr float c_minimum_distance = 1.0f;
    static constexpr float c_maximum_distance = 10.0f;

    void handle_input();

    en::camera_ptr m_impl;
    en::input& m_input;

    const game_object* m_target = nullptr; ///< The target to be followed by a camera.
    glm::vec3 m_offset = glm::vec3{0.0f}; ///< Camera's look offset from the target.

    float m_yaw = 0.0f;
    float m_pitch = 0.0f;
    float m_distance = 3.0f;
};

}
