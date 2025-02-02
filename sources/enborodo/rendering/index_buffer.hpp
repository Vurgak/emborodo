#pragma once

#include <cstddef>

#include <enborodo/configuration.hpp>

namespace en
{

class EN_API index_buffer
{
public:
    virtual ~index_buffer() = default;

    [[nodiscard]]
    virtual std::size_t count() const noexcept = 0;
};

} // en
