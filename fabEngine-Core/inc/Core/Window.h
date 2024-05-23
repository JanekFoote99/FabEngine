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

    ui16 width;
    ui16 height;

    WindowData(std::string title, ui16 width, ui16 height) :
      title(title),
      width(width),
      height(height)
    {

    }
  };

  class Window
  {
  public:
    Window(const WindowData& windowData);

    ui16 GetWidth() { return m_windowData.width; }
    ui16 GetHeight() { return m_windowData.height; }

    void SetWidth(ui16 width);
    void SetHeight(ui16 height);
    
    ui16 GetMouseOffsetX();
    ui16 GetMouseOffsetY();

    GLFWwindow* GetWindow() { return m_window; }

  private:
    int Init(const WindowData& windowData);

    GLFWwindow* m_window;
    GLFWmonitor* m_monitor;
    WindowData m_windowData;
  };
}