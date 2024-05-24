#pragma once

#include "types.h"

using namespace fabTypes;

namespace fabCoreGL
{
  class Camera
  {
  public:
    Camera(f32 near, f32 far, f32 aspectRatio, ui32 fov);
    f32m4 GetProjectionMatrix();
    f32m4 GetViewMatrix();
    f32m4 GetVPMatrix();

    void SetView(f32m4 viewMatrix);
    void SetPosition(f32v3 position);
  private:

    f32v3 m_position = { 2.0f, 2.0f, 7.0f };

    f32m4 m_proj;
    f32m4 m_view;
    f32m4 m_vp;
  };
}