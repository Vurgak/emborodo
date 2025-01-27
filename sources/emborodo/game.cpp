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

    m_shader = m_renderer->new_shader();
    m_shader->load_from_file(EM_ASSETS_PATH "shaders/default.vert", EM_ASSETS_PATH "shaders/default.frag");

    m_model = m_renderer->new_model();
    m_model->load_from_mesh(en::mesh::gen_triangle());
}

void game::update(const float delta_time)
{
    (void)delta_time;
}

void game::render() const
{
    m_renderer->render(*m_shader, *m_model);
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
