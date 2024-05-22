#include "Application.h"


namespace fabCoreGL
{
  Application* Application::s_instance = nullptr;

  Application::Application(const std::string& name, ui16 width, ui16 height)
  {
    s_instance = this;

    m_window = std::make_unique<Window>(WindowData(name, width, height));

    m_imGuiLayer = new ImGuiLayer();
    m_imGuiLayer->Init();
  }

  void Application::OnDraw()
  {
    while (m_Running)
    {
      float time = glfwGetTime();
      float delta = time - m_lastFrameTime;
      m_lastFrameTime = time;
      for (Layer* layer : m_layerStack)
      {
        layer->OnUpdate(delta);
      }

      m_imGuiLayer->Start();
      for (Layer* layer : m_layerStack)
      {
        layer->OnImGuiRender();
      }
      m_imGuiLayer->End();
    }
  }
}
