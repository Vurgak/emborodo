#pragma once

#include <enborodo/windowing/input.hpp>

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

    /// Checks whether a key was just pressed.
    [[nodiscard]]
    bool is_key_pressed(key key) override;

    /// Checks whether a key was just released.
    [[nodiscard]]
    bool is_key_released(key key) override;

    /// Checks whether a key is being held down.
    [[nodiscard]]
    bool is_key_down(key key) override;

    /// Checks whether a key is not being pressed.
    [[nodiscard]]
    bool is_key_up(key key) override;

    [[nodiscard]]
    glm::vec2 get_mouse_delta() override;

    [[nodiscard]]
    float get_mouse_scroll() override;

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

    void set_key_state(key key, key_state state);

    void set_button_state(button button, key_state state);

    std::array<key_state, magic_enum::enum_count<key>()> m_keys{};
    std::array<key_state, magic_enum::enum_count<button>()> m_buttons{};
};

using glfw_input_ptr = std::unique_ptr<glfw_input>;

}
