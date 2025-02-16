#pragma once

#include <enborodo/windowing/input.hpp>

#include <glm/vec2.hpp>

#include <magic_enum/magic_enum.hpp>

struct GLFWwindow;

namespace en
{

class glfw_window;

class glfw_input final : public input
{
public:
    explicit glfw_input(glfw_window& window);

    void update() override;

    [[nodiscard]]
    bool is_key_pressed(key key) override;

    [[nodiscard]]
    bool is_key_released(key key) override;

    [[nodiscard]]
    bool is_key_down(key key) override;

    [[nodiscard]]
    bool is_key_up(key key) override;

    [[nodiscard]]
    glm::ivec2 get_mouse_position() override;

    [[nodiscard]]
    glm::ivec2 get_mouse_delta() override;

    [[nodiscard]]
    glm::ivec2 get_scroll_movement() override;

    [[nodiscard]]
    int get_horizontal_scroll_movement() override;

    [[nodiscard]]
    int get_vertical_scroll_movement() override;

    [[nodiscard]]
    bool is_button_pressed(button button) override;

    [[nodiscard]]
    bool is_button_released(button button) override;

    [[nodiscard]]
    bool is_button_down(button button) override;

    [[nodiscard]]
    bool is_button_up(button button) override;

private:
    friend void handle_key_event(GLFWwindow*, int, int, int, int);
    friend void handle_button_event(GLFWwindow*, int, int, int);
    friend void handle_mouse_movement(GLFWwindow*, double, double);
    friend void handle_scroll_movement(GLFWwindow*, double, double);

    void set_key_state(key key, key_state state);
    void set_button_state(button button, key_state state);
    void set_mouse_position(glm::ivec2 position);
    void set_mouse_scroll_movement(glm::ivec2 scroll_movement);

    std::array<key_state, magic_enum::enum_count<key>()> m_keys{};
    std::array<key_state, magic_enum::enum_count<button>()> m_buttons{};
    glm::ivec2 m_mouse_position{};
    glm::ivec2 m_mouse_delta{};
    glm::ivec2 m_scroll_movement{};
};

using glfw_input_ptr = std::unique_ptr<glfw_input>;

}
