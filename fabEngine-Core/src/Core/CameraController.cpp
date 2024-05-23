#include "CameraController.h"

namespace fabCoreGL
{
  // Helper for Camera Movement
  static double lastX = 0;
  static double lastY = 0;

  static void mouse_callback(GLFWwindow* window, double xPos, double yPos)
  {
    // Calc offsets
    ui16 xOffset = xPos - lastX;
    ui16 yOffset = yPos - lastY;

    // Set up Variables for next frame
    lastX = xPos;
    lastY = xPos;
  }

  CameraController::CameraController() :
    m_camera(Camera(0.1f, 100.0f, 16.0f / 9.0f, 90))
  {
    lastX = Application::GetInstance().GetWindow().GetWidth() / 2;
    lastY = Application::GetInstance().GetWindow().GetHeight() / 2;

    // Set Cursor Callback for mouse movement
    glfwSetCursorPosCallback(Application::GetInstance().GetWindow().GetWindow(), mouse_callback);
  }

  void CameraController::OnUpdate(float delta)
  {
    // Camera Direction as Euler Angle
    Application::GetInstance().GetWindow();

  }




}
