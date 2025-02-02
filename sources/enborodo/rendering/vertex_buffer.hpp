#pragma once

#include <memory>

namespace en
{

class vertex_buffer
{
public:
    virtual ~vertex_buffer() = default;
};

using vertex_buffer_ptr = std::unique_ptr<vertex_buffer>();

}
