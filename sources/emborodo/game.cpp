#include "game.hpp"

#include <format>
#include <enborodo/gui/gui_window.hpp>
#include <enborodo/platform/gui/imgui/imgui_gui_controller.hpp>

namespace em
{

game::game(const std::string_view name, const int width, const int height) :
    application{name, width, height}
{
    m_gui_controller = std::make_unique<en::imgui_gui_controller>(*m_window);
}

void game::update(const float delta_time)
{
    (void)delta_time;
}

void game::render() const
{
}

void game::render_gui() const
{
    m_gui_controller->begin();

    m_gui_controller->draw_window("Debug", [this](en::gui_window& window)
    {
        window.text(std::format("FPS:        {:.1f}", 1.0f / get_frame_time()));
        window.text(std::format("Frame time: {:.4f}ms", get_frame_time() * 1000));
    });

    m_gui_controller->end();
}

}
