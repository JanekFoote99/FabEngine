#pragma once

#include "types.h"

using namespace fabTypes;

namespace fabCoreGL
{
  class Camera
  {
  public:
    Camera();
  private:
    void computeMatrices();
    f32v3 m_position;

    f32m4 m_mvp;
    f32m4 m_mv;
    f32m4 m_m;
  };
}