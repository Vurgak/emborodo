#include "gl_model.hpp"

#include <enborodo/rendering/mesh.hpp>

#include <glad/glad.h>

namespace en
{

void gl_model::load_from_mesh(const mesh& mesh)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    const auto vertices = mesh.get_vertices();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    constexpr int position_attrib = 0;
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));

    const auto indices = mesh.get_indices();
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    m_mesh = &mesh;
}

const mesh* gl_model::get_mesh() const
{
    return m_mesh;
}

unsigned int gl_model::get_vertex_array_handle() const
{
    return m_vao;
}

}
