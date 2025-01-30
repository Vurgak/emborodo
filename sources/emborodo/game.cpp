#include "game.hpp"

#include <format>

#include <enborodo/gui/gui_window.hpp>
#include <enborodo/logging/sinks/terminal_sink.hpp>
#include <enborodo/platform/gui/imgui/imgui_gui_controller.hpp>
#include <enborodo/platform/rendering/gl/gl_camera.hpp>
#include <enborodo/platform/rendering/gl/gl_texture.hpp>

namespace em
{

game::game(const std::string_view name, const int width, const int height) :
    application{name, width, height}
{
    m_frame_control.set_target_fps(60);

    m_gui_controller = std::make_unique<en::imgui_gui_controller>(*m_window);
    m_gui_controller->load_font(EM_ASSETS_PATH "fonts/OpenSans-Medium.ttf", 18);

    m_logger.set_minimum_level(en::log_level::warning);
    m_logger.add_sink<en::terminal_sink>();

    m_shader = m_renderer->new_shader();
    m_shader->load_from_file(EM_ASSETS_PATH "shaders/default.vert", EM_ASSETS_PATH "shaders/default.frag");

    m_camera = std::make_unique<en::gl_camera>();
    m_camera->set_position({1.0f, 2.0f, 3.0f});
    m_camera->set_target({0.0f, 0.0f, 0.0f});

    m_renderer->set_camera(*m_camera);

    m_image.load_from_file(EM_ASSETS_PATH "textures/logo.png");

    m_texture = std::make_unique<en::gl_texture>();
    m_texture->load_from_image(m_image);

    m_quad = en::mesh::generate_quad();
    m_model = m_renderer->new_model();
    m_model->load_from_mesh(m_quad);
}

void game::update(const float delta_time)
{
    m_logger.log(en::log_level::debug, "delta_time: {}", delta_time);
}

void game::render() const
{
    m_renderer->render(*m_shader, *m_model, *m_texture);
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
