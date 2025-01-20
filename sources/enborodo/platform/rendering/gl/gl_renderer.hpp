#pragma once

#include <enborodo/rendering/renderer.hpp>
#include <enborodo/configuration.hpp>

namespace en
{

class EN_API gl_renderer final : public renderer
{
    void clear(color color) override;
};

}
