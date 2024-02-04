#include "Application.h"


namespace fabCoreGL
{
  Application* Application::s_instance = nullptr;

  Application::Application(const std::string& name, ui8 width, ui8 height)
  {
    s_instance = this;

    m_window = std::make_unique<Window>(Window(WindowData(name, width, height)));

    m_imGuiLayer = new ImGuiLayer();
  }
}
