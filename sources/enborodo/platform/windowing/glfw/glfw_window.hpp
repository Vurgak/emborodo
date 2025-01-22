#pragma once

#include <enborodo/rendering/color.hpp>
#include <enborodo/windowing/window.hpp>

struct GLFWwindow;

namespace en
{

class EN_API glfw_window final : public window
{
public:
    ~glfw_window() override;

    void open(std::string_view title, int width, int height) override;

    void close() override;

    bool is_open() override;

    void poll_events() override;

    void display() override;

    [[nodiscard]]
    window_backend get_backend() const override;

    [[nodiscard]]
    void* get_handle() override;

private:
    static int s_instance_count;

    GLFWwindow* m_handle = nullptr;
};

}
