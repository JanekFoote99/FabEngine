#include "CameraController.h"
#include <algorithm>
#include "glm/ext/matrix_transform.hpp"

namespace fabCoreGL
{
  // Helper for Camera Movement
  static double lastX = 0;
  static double lastY = 0;

  static float pitch = 0.0f;
  static float yaw = -90.0f;

  // Helper to calculate the right vector representing the x axis of the camera
  f32v3 up(0.0f, 1.0f, 0.0f);

  f32v3 cameraPos(0.0f, 0.0f, 3.0f);
  f32v3 cameraRight;
  f32v3 cameraFront(0.0f, 0.0f, -1.0f);
  f32v3 cameraUp(0.0f, 1.0f, 0.0f);

  CameraController::CameraController() :
    m_camera(Camera(0.1f, 100.0f, 16.0f / 9.0f, 90)),
    m_cameraPos(f32v3(1.0f, 1.0f, 3.0f))
  {
    lastX = Application::GetInstance().GetWindow().GetWidth() / 2;
    lastY = Application::GetInstance().GetWindow().GetHeight() / 2;

    // Set Cursor Callback for mouse movement
    glfwSetCursorPosCallback(Application::GetInstance().GetWindow().GetWindow(), mouse_callback);
  }

  static void mouse_callback(GLFWwindow* window, double xPos, double yPos)
  {
    // Calc offsets
    ui16 xOffset = xPos - lastX;
    ui16 yOffset = yPos - lastY;

    // Set up Variables for next frame
    lastX = xPos;
    lastY = xPos;

    yaw += xOffset;
    pitch += yOffset;

    pitch = std::clamp(pitch, -89.0f, 89.0f);
  }

  // OpenGL Camera Tutorial: https://learnopengl.com/Getting-started/Camera
  f32m4 CameraController::CalculateView()
  {
    f32v3 cameraPos(0.0f, 0.0f, 3.0f);

    f32v3 cameraTarget(0.0f);
    f32v3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    // Front vector uses Euler Angles Yaw and Pitch to calculate Rotations
    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::normalize(cameraFront);
    // Right Vector of the Camera is the cross product of the view Direction and the up vector
    cameraRight = glm::normalize(glm::cross(cameraFront, up));
    cameraUp = glm::cross(cameraRight, cameraFront);

    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  }

  void CameraController::OnUpdate(float delta)
  {
    GLFWwindow* window = Application::GetInstance().GetWindow().GetWindow();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      m_cameraPos += cameraFront * delta * m_cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
      m_cameraPos -= cameraFront * delta * m_cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
      m_cameraPos += cameraRight * delta * m_cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
      m_cameraPos -= cameraRight * delta * m_cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
      m_cameraPos.y += 0.001f * m_cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
      m_cameraPos.y -= 0.001f * m_cameraSpeed;
    }

    m_camera.SetPosition(m_cameraPos);
    m_camera.SetView(CalculateView());
  }
}
