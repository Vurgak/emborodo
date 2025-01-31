#pragma once

#include <memory>

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

    en::shader_ptr m_shader;
    en::camera_ptr m_camera;

    en::texture_ptr m_texture;
    en::mesh m_quad;
    en::model_ptr m_model;
};

}
