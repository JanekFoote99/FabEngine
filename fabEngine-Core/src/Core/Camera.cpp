#include <Camera.h>
#include <glm/ext/matrix_clip_space.hpp>

namespace fabCoreGL
{
  Camera::Camera(f32 near, f32 far, f32 aspectRatio, ui32 fov) :
    m_proj(glm::perspective(glm::radians(static_cast<float>(fov)), 4.0f / 3.0f, near, far)),
    m_view(f32m4(1.0f))
  {
    m_mv = m_proj * m_view;
  }

  void Camera::updateView(double xOffset, double yOffset)
  {
    
  }

  f32m4 Camera::getProjectionMatrix()
  {
    return m_proj;
  }
  
  f32m4 Camera::getViewMatrix()
  {
    return m_view;
  }

  f32m4 Camera::getMVMatrix()
  {
    return m_mv;
  }
}