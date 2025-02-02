#include "gl_index_buffer.hpp"

#include <glad/glad.h>

namespace en
{

gl_index_buffer::~gl_index_buffer()
{
    glDeleteBuffers(1, &m_ebo);
}

void gl_index_buffer::load(const std::span<const unsigned int> indices)
{
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(indices[0])), indices.data(), GL_STATIC_DRAW);

    m_count = indices.size();
}

std::size_t gl_index_buffer::count() const noexcept
{
    return m_count;
}

}
