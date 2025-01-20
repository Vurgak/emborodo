#pragma once

#include <memory>

#include <enborodo/rendering/color.hpp>
#include <enborodo/application.hpp>

namespace en
{

class EN_API renderer
{
public:
    virtual ~renderer() = default;

    static renderer& create();

    static renderer& get_instance();

    virtual void clear(color color = color::black) = 0;

private:
    static std::unique_ptr<renderer> s_instance;
};

}
