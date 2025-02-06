#include "game.hpp"

#include <format>

#include <enborodo/gui/gui_window.hpp>
#include <enborodo/logging/sinks/terminal_sink.hpp>
#include <enborodo/platform/gui/imgui/imgui_gui_controller.hpp>
#include <enborodo/windowing/input.hpp>

namespace em
{

game::game(const std::string_view name, en::application_configuration& configuration) :
    application{name, configuration},
    m_input{m_window->get_input()},
    m_camera{m_renderer->new_camera(), m_input}
{
    m_window->set_cursor_enabled(false);

    m_logger.add_sink<en::terminal_sink>();
    m_gui_controller->load_font(EM_ASSETS_PATH "fonts/OpenSans-Medium.ttf", 20);

    m_shader = m_renderer->new_shader();
    m_shader->load_from_file(EM_ASSETS_PATH "shaders/default.vert", EM_ASSETS_PATH "shaders/default.frag");
    m_shader->set_uniform("u_AmbientLightStrength", 0.2f);
    m_shader->set_uniform("u_AmbientLightColor", glm::vec3{1.0f});

    m_renderer->set_camera(m_camera.get_impl());
    m_camera.set_target(m_player);

    m_texture = m_renderer->new_texture();
    m_texture->load_from_file(EM_ASSETS_PATH "textures/viking_room.png");

    m_quad = en::mesh::load_from_file(EM_ASSETS_PATH "models/viking_room.obj");
    m_model = m_renderer->new_model();
    m_model->load_from_mesh(m_quad);
}

void game::update([[maybe_unused]] const float delta_time)
{
    if (m_input.is_key_released(en::key::escape))
        m_window->close();

    constexpr float move_speed = 8.0f;
    if (m_input.is_key_down(en::key::a))
        m_player.position.x -= move_speed * delta_time;
    if (m_input.is_key_down(en::key::d))
        m_player.position.x += move_speed * delta_time;

    if (m_input.is_key_down(en::key::left_alt))
    {
        if (!m_mouse_shown)
        {
            m_mouse_shown = true;
            m_window->set_cursor_enabled(true);

            const auto window_size = m_window->get_window_size();
            m_window->set_cursor_position(window_size.x / 2, window_size.y / 2);
        }
    }
    else
    {
        if (m_mouse_shown)
        {
            m_mouse_shown = false;
            m_window->set_cursor_enabled(false);
        }

        m_camera.update();
    }
}

void game::render() const
{
    m_renderer->render(*m_shader, *m_model, *m_texture);
}

void game::render_gui()
{
    m_gui_controller->draw_window("Debug", [this](auto& window) { draw_debug_window(window); });
}

void game::draw_debug_window(en::gui_window& window)
{
    window.text(std::format("FPS: {:.1f}", 1000.0f / static_cast<float>(m_frame_control.get_frame_time())));
    window.text(std::format("Frame time: {}ms", m_frame_control.get_frame_time()));
}

}
