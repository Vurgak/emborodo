#include "game.hpp"

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

    m_gui_controller->draw_window("Test window", [](en::gui_window& window)
    {
        window.text("Hello, world!");
    });

    m_gui_controller->end();
}

}
