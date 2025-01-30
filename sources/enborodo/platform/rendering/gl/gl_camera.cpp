#include "gl_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace en
{

gl_camera::gl_camera()
{
    m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void gl_camera::set_position(const glm::vec3 position)
{
    m_dirty = true;
    m_position = position;
}

void gl_camera::set_target(glm::vec3 target)
{
    m_dirty = true;
    m_target = target;
}

const glm::mat4& gl_camera::get_view()
{
    if (m_dirty)
    {
        m_dirty = false;
        m_view = glm::lookAt(m_position, m_target, m_up);
    }

    return m_view;
}

const glm::mat4& gl_camera::get_projection()
{
    return m_projection;
}

}
