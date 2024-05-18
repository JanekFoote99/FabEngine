#pragma once

#include <string>
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "types.h"

using namespace fabTypes;

namespace fabCoreGL
{
  struct WindowData
  {
    std::string title;
    ui16 m_width;
    ui16 m_height;
  };

  class Window
  {
  public:
    Window(const WindowData& windowData);

    ui16 GetWidth() { return m_windowData.m_width; }
    ui16 GetHeight() { return m_windowData.m_height; }

    void SetWidth(ui16 width);
    void SetHeight(ui16 height);

    GLFWwindow* GetWindow() { return m_window; }

  private:
    int Init(const WindowData& windowData);

    GLFWwindow* m_window;
    GLFWmonitor* m_monitor;
    WindowData m_windowData;
  };
}