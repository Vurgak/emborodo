#pragma once

#include <memory>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API vertex_buffer
{
public:
    virtual ~vertex_buffer() = default;
};

using vertex_buffer_ptr = std::unique_ptr<vertex_buffer>();

}
