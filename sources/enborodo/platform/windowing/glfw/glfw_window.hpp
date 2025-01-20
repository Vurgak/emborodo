#pragma once

#include <enborodo/windowing/window.hpp>

struct GLFWwindow;

namespace en
{

class EN_API glfw_window final : public window
{
public:
    ~glfw_window();

    void open(std::string_view title, int width, int height) override;

    void close() override;

    bool is_open() override;

    void poll_events() override;

    void display() override;

private:
    static int s_instance_count;

    GLFWwindow* m_handle;
};

}
