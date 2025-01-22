#include "application.hpp"

#include <chrono>
#include <iostream>

#include <enborodo/platform/windowing/glfw/glfw_window.hpp>
#include <enborodo/gui/gui_window.hpp>
#include <enborodo/rendering/renderer.hpp>

namespace en
{

application::application(const std::string_view name, const int width, const int height) :
    m_window{std::make_unique<glfw_window>()}
{
    m_window->open(name, width, height);
    m_renderer = &renderer::create();
}

void application::run()
{
    while (m_window->is_open())
    {
        const auto frame_start = std::chrono::high_resolution_clock::now();

        m_window->poll_events();
        update(m_frame_time);

        m_renderer->clear();
        render();
        render_gui();
        m_window->display();

        const auto frame_end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float> frame_elapsed = frame_end - frame_start;
        m_frame_time = frame_elapsed.count();
    }
}

float application::get_frame_time() const
{
    return m_frame_time;
}

}
