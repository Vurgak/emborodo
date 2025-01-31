#include "gl_renderer.hpp"

// TODO: Replace standard assert.
#include <cassert>

#include <enborodo/platform/rendering/gl/gl_camera.hpp>
#include <enborodo/platform/rendering/gl/gl_model.hpp>
#include <enborodo/platform/rendering/gl/gl_shader.hpp>
#include <enborodo/platform/rendering/gl/gl_texture.hpp>
#include <enborodo/rendering/mesh.hpp>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>

namespace en
{

shader_ptr gl_renderer::new_shader()
{
    return std::make_unique<gl_shader>();
}

model_ptr gl_renderer::new_model()
{
    return std::make_unique<gl_model>();
}

void gl_renderer::clear(const color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_renderer::render(const shader& shader, const model& model, const texture& texture) const
{
    assert(m_camera != nullptr);

    const auto& program = dynamic_cast<const gl_shader&>(shader).get_program_handle();
    const auto& _model = dynamic_cast<const gl_model&>(model);
    const auto index_count = static_cast<GLsizei>(_model.get_mesh()->get_indices().size());
    const auto& _texture = dynamic_cast<const gl_texture&>(texture);

    glUseProgram(program);
    shader.set_uniform("u_Model", glm::mat4(1.0f));
    shader.set_uniform("u_View", m_camera->get_view());
    shader.set_uniform("u_Projection", m_camera->get_projection());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.get_handle());
    glBindVertexArray(_model.get_vertex_array_handle());
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}

void gl_renderer::set_camera(camera& camera)
{
    m_camera = &camera;
}

}
