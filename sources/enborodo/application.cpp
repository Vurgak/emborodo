#include "application.hpp"

#include <chrono>

#include <enborodo/platform/gui/imgui/imgui_gui_controller.hpp>

namespace en
{

application::application(const std::string_view name, const application_configuration& configuration) :
    m_logger{configuration.logging},
    m_window{window::open(name, configuration.window, configuration.rendering)},
    m_renderer{renderer::create(renderer_backend::opengl)},
    m_gui_controller{std::make_unique<imgui_gui_controller>(*m_window)}
{
    m_frame_control.set_target_fps(configuration.window.fps_limit);
}

void application::run()
{
    while (m_window->is_open())
    {
        m_window->poll_events();
        update(m_frame_control.get_delta_time());

        m_renderer->clear();

        render();

        m_gui_controller->begin();
        render_gui();
        m_gui_controller->end();

        m_window->display();

        m_frame_control.end_frame();
    }
}

}
