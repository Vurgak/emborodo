#include "gl_texture.hpp"

#include <glad/glad.h>

#include <enborodo/rendering/image.hpp>

namespace en
{

gl_texture::gl_texture()
{
    glGenTextures(1, &m_handle);
}

gl_texture::~gl_texture()
{
    glDeleteTextures(1, &m_handle);
}

void gl_texture::load_from_image(const image& image)
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const auto width = static_cast<GLsizei>(image.get_width());
    const auto height = static_cast<GLsizei>(image.get_height());
    const auto data = image.get_data().data();
    const auto format = image.get_channels() == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int gl_texture::get_handle() const
{
    return m_handle;
}

}
