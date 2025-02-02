#pragma once

#include <span>

#include <enborodo/rendering/vertex_buffer.hpp>

namespace en
{

class EN_API gl_vertex_buffer final : public vertex_buffer
{
public:
    ~gl_vertex_buffer() override;

    void load(std::span<const float> vertices);

    [[nodiscard]]
    bool is_loaded() const noexcept;

private:
    unsigned int m_vbo = 0;
};

}
