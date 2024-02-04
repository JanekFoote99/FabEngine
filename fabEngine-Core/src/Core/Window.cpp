#include <Window.h>

using namespace fabCoreGL;

Window::Window(const WindowData& data)
  : m_windowData(data)
{
  Init(data);
}

Window::~Window()
{
  delete m_window;
  delete m_monitor;
  glfwTerminate();
}

void Window::SetHeight(ui8 height)
{
  if (height > 1440)
  {
    std::cout << "Couldn't set Window height. Values must range between 0 => 1440" << std::endl;
    return;
  }
  m_windowData.m_height = height;
}

void Window::SetWidth(ui8 width)
{
  if (width > 2560)
  {
    std::cout << "Couldn't set Window width. Values must range between 0 => 2560" << std::endl;
  }
  m_windowData.m_width = width;
}

int Window::Init(const WindowData& data)
{
  if (!glfwInit())
  {
    std::cerr << "GLFW couldn't be Initialized";
    return -1;
  }

  m_monitor = glfwGetPrimaryMonitor();
  m_window = glfwCreateWindow(data.m_width, data.m_height, data.title.c_str(), m_monitor, NULL);

  glfwMakeContextCurrent(m_window);
}