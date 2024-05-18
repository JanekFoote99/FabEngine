#include "Application.h"


namespace fabCoreGL
{
  Application* Application::s_instance = nullptr;

  Application::Application(const std::string& name, ui16 width, ui16 height)
  {
    s_instance = this;

    m_window = std::make_unique<Window>(Window(WindowData(name, width, height)));

    m_imGuiLayer = new ImGuiLayer();
    m_imGuiLayer->Init();
  }

  void Application::OnDraw()
  {
    m_imGuiLayer->Start();

    m_imGuiLayer->End();
  }
}
