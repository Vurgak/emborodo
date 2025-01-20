#pragma once

#include <memory>

#include <enborodo/windowing/window.hpp>
#include <enborodo/configuration.hpp>

namespace en
{

class EN_API application
{
public:
    application(std::string_view name, int width, int height);
    virtual ~application() = default;

    void run();

private:
    virtual void update(float delta_time) = 0;
    virtual void render() const = 0;

    std::unique_ptr<window> m_window{};
};

}
