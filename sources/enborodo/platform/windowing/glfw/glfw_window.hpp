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

    void poll_events() override;

    [[nodiscard]]
    input& get_input() override;

    void display() override;

    [[nodiscard]]
    window_backend get_backend() const override;

    [[nodiscard]]
    void* get_handle() override;

private:
    bool open_with_opengl(std::string_view title);

    static int s_instance_count;

    const window_configuration& m_configuration;
    const rendering_configuration& m_rendering_configuration;

    GLFWwindow* m_handle = nullptr;
    glfw_input_ptr m_input = nullptr;
};

}
