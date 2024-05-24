#include <Camera.h>
#include <glm/ext/matrix_clip_space.hpp>

namespace fabCoreGL
{
  Camera::Camera(f32 near, f32 far, f32 aspectRatio, ui32 fov) :
    m_proj(glm::perspective(glm::radians(static_cast<float>(fov)), 4.0f / 3.0f, near, far)),
    m_view(f32m4(1.0f))
  {
    m_vp = m_proj * m_view;
  }

  void Camera::SetPosition(f32v3 position)
  {
    m_position = position;
  }

  void Camera::SetView(f32m4 viewMatrix)
  {
    m_view = viewMatrix;
  }

  f32m4 Camera::GetProjectionMatrix()
  {
    return m_proj;
  }
  
  f32m4 Camera::GetViewMatrix()
  {
    return m_view;
  }

  f32m4 Camera::GetVPMatrix()
  {
    return m_vp;
  }
}