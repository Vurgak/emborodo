#pragma once

#include <memory>

#include <emborodo/game_objects/third_person_camera.hpp>

#include <enborodo/application.hpp>
#include <enborodo/logging/logger.hpp>
#include <enborodo/rendering/camera.hpp>
#include <enborodo/rendering/mesh.hpp>
#include <enborodo/rendering/model.hpp>
#include <enborodo/rendering/texture.hpp>

namespace en
{

class gui_window;

}

namespace em
{

class game final : public en::application
{
public:
    game(std::string_view name, en::application_configuration& configuration);

protected:
    void update(float delta_time) override;
    void render() const override;
    void render_gui() override;

private:
    void draw_debug_window(en::gui_window& window);

    en::input& m_input;
    bool m_mouse_shown = false;

    en::shader_ptr m_shader;

    third_person_camera m_camera;

    game_object m_player{};

    en::texture_ptr m_texture;
    en::mesh m_mesh;
    en::model_ptr m_model;
};

}
