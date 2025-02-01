#pragma once

#include <unordered_map>

#include <enborodo/windowing/input.hpp>

#include <magic_enum/magic_enum.hpp>

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
    bool is_button_pressed() override;

    [[nodiscard]]
    bool is_button_released() override;

    [[nodiscard]]
    bool is_button_down() override;

    [[nodiscard]]
    bool is_button_up() override;

    void set_key_pressed(key key);

    void set_key_released(key key);

private:
    enum key_state
    {
        down,
        pressed,
        released,
        up,
    };

    std::array<key_state, magic_enum::enum_count<key>()> m_keys{};
};

using glfw_input_ptr = std::unique_ptr<glfw_input>;

}
