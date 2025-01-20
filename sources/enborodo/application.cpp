#include "application.hpp"

#include <iostream>

#include <enborodo/platform/windowing/glfw/glfw_window.hpp>
#include <enborodo/rendering/renderer.hpp>

namespace en
{

application::application(std::string_view name, int width, int height) :
    m_window{std::make_unique<glfw_window>()}
{
    m_window->open(name, width, height);
    m_renderer = &renderer::create();
}

void application::run()
{
    while (m_window->is_open())
    {
        m_window->poll_events();

        m_renderer->clear();
        m_window->display();
    }
}

}
