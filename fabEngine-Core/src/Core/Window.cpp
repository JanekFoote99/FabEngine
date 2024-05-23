#include <Window.h>


namespace fabCoreGL
{
  Window::Window(const WindowData& data)
    : m_windowData(data)
  {
    Init(data);
  }

  void Window::SetHeight(ui16 height)
  {
    if (height > 1440)
    {
      std::cout << "Couldn't set Window height. Values must range between 0 => 1440" << std::endl;
      m_windowData.height = 1440;
      return;
    }
    m_windowData.height = height;
  }

  void Window::SetWidth(ui16 width)
  {
    if (width > 2560)
    {
      std::cout << "Couldn't set Window width. Values must range between 0 => 2560" << std::endl;
      m_windowData.width = 2560;
      return;
    }
    m_windowData.width = width;
  }

  ui16 Window::GetMouseOffsetX()
  {

  }

  ui16 Window::GetMouseOffsetY()
  {
    
  }

  int Window::Init(const WindowData& data)
  {
    if (!glfwInit())
    {
      std::cerr << "GLFW couldn't be Initialized";
      return -1;
    }

    m_monitor = glfwGetPrimaryMonitor();
    m_window = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);

    // enable VSYNC
    //glfwSwapInterval(1);

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, true);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(m_window);
  }
}
