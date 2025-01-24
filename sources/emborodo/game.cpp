#include "game.hpp"

#include <format>
#include <enborodo/gui/gui_window.hpp>
#include <enborodo/platform/gui/imgui/imgui_gui_controller.hpp>

namespace em
{

game::game(const std::string_view name, const int width, const int height) :
    application{name, width, height}
{
    m_frame_control.set_target_fps(60);

    m_gui_controller = std::make_unique<en::imgui_gui_controller>(*m_window);
    m_gui_controller->load_font(EM_ASSETS_PATH "fonts/OpenSans-Medium.ttf", 18);
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
        window.text(std::format("FPS: {:.1f}", 1000.0f / static_cast<float>(m_frame_control.get_frame_time())));
        window.text(std::format("Frame time: {}ms", m_frame_control.get_frame_time()));
    });

    m_gui_controller->end();
}

}
