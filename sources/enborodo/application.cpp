#include "application.hpp"

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
        m_window->poll_events();
        update(13.3333f);

        m_renderer->clear();
        render();
        render_gui();
        m_window->display();
    }
}

}
