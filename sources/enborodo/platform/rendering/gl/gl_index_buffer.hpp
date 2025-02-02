#pragma once

#include <span>

#include <enborodo/rendering/index_buffer.hpp>

namespace en
{

class EN_API gl_index_buffer final : public index_buffer
{
public:
    ~gl_index_buffer() override;

    void load(std::span<const unsigned int> indices);

    [[nodiscard]]
    std::size_t count() const noexcept override;

private:
    unsigned int m_ebo = 0;
    std::size_t m_count = 0;
};

}
