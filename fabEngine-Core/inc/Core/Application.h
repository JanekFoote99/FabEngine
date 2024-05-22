#pragma once

#include "Window.h"

#include "ImGuiLayer.h"
#include <LayerStack.h>

namespace fabCoreGL
{
  class Application
  {
  public:
    Application(const std::string& name = "fabEngine", ui16 width = 1280, ui16 height = 720);

    void OnDraw();

    static Application& GetInstance() { return *s_instance; }
    Window& GetWindow() { return *m_window; }
  private:
    std::unique_ptr<Window> m_window;
    static Application* s_instance;

    ImGuiLayer* m_imGuiLayer;
    bool m_Running = true;
    f32 m_lastFrameTime = 0.0f;
  private:
    LayerStack m_layerStack;
  };
}
