#include "gl_vertex_buffer.hpp"

#include <enborodo/rendering/vertex.hpp>

#include <glad/glad.h>

namespace en
{
struct vertex;

gl_vertex_buffer::~gl_vertex_buffer()
{
    glDeleteBuffers(1, &m_vbo);
}

void gl_vertex_buffer::load(const std::span<const vertex> vertices)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(vertex)), vertices.data(), GL_STATIC_DRAW);

    constexpr int stride = sizeof(vertex);

    constexpr int position_attribute_index = 0;
    const auto position_offset = reinterpret_cast<void*>(offsetof(vertex, position));
    glEnableVertexAttribArray(position_attribute_index);
    glVertexAttribPointer(position_attribute_index, 3, GL_FLOAT, GL_FALSE, stride, position_offset);

    constexpr int normal_attribute_index = 1;
    const auto normal_offset = reinterpret_cast<void*>(offsetof(vertex, normal));
    glEnableVertexAttribArray(normal_attribute_index);
    glVertexAttribPointer(normal_attribute_index, 3, GL_FLOAT, GL_FALSE, stride, normal_offset);

    constexpr int tex_coords_attribute_index = 2;
    const auto tex_coord_offset = reinterpret_cast<void*>(offsetof(vertex, tex_coord));
    glEnableVertexAttribArray(tex_coords_attribute_index);
    glVertexAttribPointer(tex_coords_attribute_index, 2, GL_FLOAT, GL_FALSE, stride, tex_coord_offset);
}

bool gl_vertex_buffer::is_loaded() const noexcept
{
    return m_vbo != 0;
}

}
