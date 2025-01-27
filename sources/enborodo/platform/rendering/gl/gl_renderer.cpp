#include "gl_renderer.hpp"

#include <enborodo/platform/rendering/gl/gl_model.hpp>
#include <enborodo/platform/rendering/gl/gl_shader.hpp>
#include <enborodo/rendering/mesh.hpp>

#include <glad/glad.h>

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

void gl_renderer::render(const shader& shader, const model& model) const
{
    const auto program = dynamic_cast<const gl_shader&>(shader).get_program_handle();
    const auto _model = dynamic_cast<const gl_model&>(model);
    const auto index_count =  static_cast<GLsizei>(_model.get_mesh()->get_indices().size());

    glUseProgram(program);
    glBindVertexArray(_model.get_vertex_array_handle());
    glDrawArrays(GL_TRIANGLES, 0, index_count);
}

}
