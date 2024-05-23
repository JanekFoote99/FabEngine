#pragma once
#include "Camera.h"
#include "Application.h"

namespace fabCoreGL
{
  class CameraController
  {
  public:
    CameraController();

    void OnUpdate(float delta);
    double GetXOffset();
    double GetYOffset();
  private:
    Camera m_camera;
  };
}