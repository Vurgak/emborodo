#include "gl_model.hpp"

#include <enborodo/rendering/mesh.hpp>

#include <glad/glad.h>

namespace en
{

void gl_model::load_from_mesh(const mesh& mesh)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    m_vertex_buffer.load(mesh.get_vertices());
    m_index_buffer.load(mesh.get_indices());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const gl_vertex_buffer& gl_model::get_vertex_buffer() const noexcept
{
    return m_vertex_buffer;
}

const gl_index_buffer& gl_model::get_index_buffer() const noexcept
{
    return m_index_buffer;
}

unsigned int gl_model::get_vertex_array_handle() const
{
    return m_vao;
}

}
