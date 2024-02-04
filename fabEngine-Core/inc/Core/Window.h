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
    ui8 m_width;
    ui8 m_height;
  };

  class Window
  {
  public:
    Window(const WindowData& windowData);
    ~Window();

    ui8 GetWidth() { return m_windowData.m_width; }
    ui8 GetHeight() { return m_windowData.m_height; }

    void SetWidth(ui8 width);
    void SetHeight(ui8 height);

    GLFWwindow* GetWindow() { return m_window; }

  private:
    int Init(const WindowData& windowData);

    GLFWwindow* m_window;
    GLFWmonitor* m_monitor;
    WindowData m_windowData;
  };
}