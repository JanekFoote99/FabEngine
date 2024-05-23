#pragma once

#include "types.h"

using namespace fabTypes;

namespace fabCoreGL
{
  class Camera
  {
  public:
    Camera(f32 near, f32 far, f32 aspectRatio, ui32 fov);
    f32m4 getProjectionMatrix();
    f32m4 getViewMatrix();
    f32m4 getMVMatrix();

    void updateView(double xOffset, double yOffset);
  private:

    f32v3 m_position = { 2.0f, 2.0f, 7.0f };

    f32m4 m_proj;
    f32m4 m_view;
    f32m4 m_mv;
  };
}