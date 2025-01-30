#pragma once

#include <memory>

#include <enborodo/gui/gui_controller.hpp>
#include <enborodo/application.hpp>
#include <enborodo/rendering/camera.hpp>
#include <enborodo/rendering/image.hpp>
#include <enborodo/rendering/mesh.hpp>
#include <enborodo/rendering/model.hpp>
#include <enborodo/rendering/texture.hpp>

namespace em
{

class game final : public en::application
{
public:
    game(std::string_view name, int width, int height);

protected:
    void update(float delta_time) override;
    void render() const override;
    void render_gui() const override;

private:
    std::unique_ptr<en::gui_controller> m_gui_controller;

    en::shader_ptr m_shader;

    en::camera_ptr m_camera;

    en::image m_image;
    en::texture_ptr m_texture;

    en::mesh m_quad;
    en::model_ptr m_model;
};

}
