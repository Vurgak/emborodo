#include "gl_renderer.hpp"

#include <glad/glad.h>

namespace en
{

void gl_renderer::clear(color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
