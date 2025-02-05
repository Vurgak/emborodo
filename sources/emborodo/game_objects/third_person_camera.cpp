#include "third_person_camera.hpp"

#include <algorithm>

#include <glm/trigonometric.hpp>

#include <enborodo/utilities/math.hpp>
#include <enborodo/windowing/input.hpp>

namespace em
{

third_person_camera::third_person_camera(en::camera_ptr&& camera, en::input& input) :
    m_impl{std::move(camera)}, m_input{input}
{
}

void third_person_camera::set_target(const game_object& target, const glm::vec3 offset)
{
    m_target = &target;
    m_offset = offset;
}

void third_person_camera::update()
{
    handle_input();

    const auto horizontal_distance = m_distance * std::cos(glm::radians(m_pitch));
    const auto vertical_distance = m_distance * std::sin(glm::radians(m_pitch));
    const auto offset_x = horizontal_distance * std::sin(glm::radians(m_yaw));
    const auto offset_y = horizontal_distance * std::cos(glm::radians(m_yaw));

    const auto target = m_target->position + m_offset;
    const glm::vec3 camera_position{
        target.x - offset_x,
        target.y + vertical_distance,
        target.z - offset_y,
    };

    m_impl->set_position(camera_position);
    m_impl->look_at(m_target->position);
}

en::camera& third_person_camera::get_impl() const
{
    return *m_impl;
}

void third_person_camera::handle_input()
{
    const auto mouse_delta = m_input.get_mouse_delta();
    m_yaw = en::wrap(m_yaw + static_cast<float>(mouse_delta.x) * c_camera_sensitivity, 0.0f, 360.f);
    m_pitch = std::clamp(m_pitch + static_cast<float>(mouse_delta.y) * c_camera_sensitivity, -89.9f, 89.9f);

    const auto vertical_scroll = m_input.get_scroll_movement().y;
    m_distance = std::clamp(m_distance - static_cast<float>(vertical_scroll) * c_zoom_sensitivity, c_minimum_distance, c_maximum_distance);
}

}
