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
    f32m4 CalculateView();

    Camera GetCamera() { return m_camera; }
    f32v3 GetCameraPosition() { return m_cameraPos; }
  private:
    Camera m_camera;
    f32v3 m_cameraPos;
    f32 m_cameraSpeed = 5.0f;
  };
}