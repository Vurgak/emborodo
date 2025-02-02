#include "gl_vertex_buffer.hpp"

#include <glad/glad.h>

namespace en
{

gl_vertex_buffer::~gl_vertex_buffer()
{
    glDeleteBuffers(1, &m_vbo);
}

void gl_vertex_buffer::load(const std::span<const float> vertices)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

    constexpr int position_attrib = 0;
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));

    constexpr int tex_coords_attrib = 1;
    glEnableVertexAttribArray(tex_coords_attrib);
    glVertexAttribPointer(tex_coords_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
}

bool gl_vertex_buffer::is_loaded() const noexcept
{
    return m_vbo != 0;
}

}
