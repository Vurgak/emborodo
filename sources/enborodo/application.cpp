#include "application.hpp"

#include <chrono>

#include <enborodo/platform/windowing/glfw/glfw_window.hpp>

namespace en
{

application::application(const std::string_view name, const int width, const int height)
{
    m_window = window::create(window_backend::glfw);
    m_window->open(name, width, height);

    m_renderer = renderer::create(renderer_backend::opengl);
}

void application::run()
{
    while (m_window->is_open())
    {
        m_window->poll_events();
        update(m_frame_control.get_delta_time());

        m_renderer->clear();
        render();
        render_gui();
        m_window->display();

        m_frame_control.end_frame();
    }
}

}
