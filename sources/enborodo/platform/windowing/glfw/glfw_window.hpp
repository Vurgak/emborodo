#pragma once

#include <enborodo/platform/windowing/glfw/glfw_input.hpp>
#include <enborodo/windowing/window.hpp>

struct GLFWwindow;

namespace en
{

class EN_API glfw_window final : public window
{
public:
    glfw_window(
        const window_configuration& window_configuration,
        const rendering_configuration& rendering_configuration);

    ~glfw_window() override;

    void open(std::string_view title) override;

    void close() override;

    bool is_open() override;

    [[nodiscard]]
    glm::ivec2 get_window_size() const override;

    void set_cursor_enabled(bool enabled) override;

    void set_cursor_position(int horizontal_position, int vertical_position) override;

    [[nodiscard]]
    input& get_input() override;

    void poll_events() override;

    void display() override;

    [[nodiscard]]
    window_backend get_backend() const override;

    [[nodiscard]]
    void* get_handle() override;

private:
    bool open_with_opengl(std::string_view title);

private:
    static int s_instance_count;

    const window_configuration& m_configuration;
    const rendering_configuration& m_rendering_configuration;

    GLFWwindow* m_handle = nullptr;
    glfw_input_ptr m_input = nullptr;
};

}
