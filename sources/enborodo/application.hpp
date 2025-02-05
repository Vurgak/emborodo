#pragma once

#include <memory>

#include <enborodo/configuration.hpp>
#include <enborodo/configuration/application_configuration.hpp>
#include <enborodo/gui/gui_controller.hpp>
#include <enborodo/logging/logger.hpp>
#include <enborodo/rendering/renderer.hpp>
#include <enborodo/windowing/frame_control.hpp>
#include <enborodo/windowing/window.hpp>

namespace en
{

class EN_API application
{
public:
    application(std::string_view name, const application_configuration& configuration);
    virtual ~application() = default;

    void run();

protected:
    virtual void update(float delta_time) = 0;
    virtual void render() const = 0;
    virtual void render_gui() = 0;

    window_ptr m_window = nullptr;
    renderer_ptr m_renderer = nullptr;
    gui_controller_ptr m_gui_controller;
    frame_control m_frame_control{};
    logger m_logger;
};

}
