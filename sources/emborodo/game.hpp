#pragma once

#include <memory>

#include <enborodo/gui/gui_controller.hpp>
#include <enborodo/application.hpp>

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
};

}
