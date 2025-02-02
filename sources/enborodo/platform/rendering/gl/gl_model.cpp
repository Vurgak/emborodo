#include "gl_model.hpp"

#include <enborodo/rendering/mesh.hpp>

#include <glad/glad.h>

namespace en
{

void gl_model::load_from_mesh(const mesh& mesh)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    vertex_buffer.load(mesh.get_vertices());

    const auto indices = mesh.get_indices();
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(indices[0])), indices.data(), GL_STATIC_DRAW);
    m_index_count = indices.size();
}

std::size_t gl_model::get_index_count() const noexcept
{
    return m_index_count;
}

unsigned int gl_model::get_vertex_array_handle() const
{
    return m_vao;
}

}
