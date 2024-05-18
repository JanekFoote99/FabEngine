#include <ImGuiLayer.h>
#include <Application.h>
#include <glad/glad.h>


namespace fabCoreGL
{
  ImGuiLayer::ImGuiLayer()
  {
  }

  void ImGuiLayer::Init()
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    Application& app = Application::GetInstance();
    GLFWwindow* window = app.GetWindow().GetWindow();

    ImGui_ImplGlfw_InitForOpenGL(window, true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize OpenGL context" << std::endl;
    }
    ImGui_ImplOpenGL3_Init("version 460");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
  }

  void ImGuiLayer::Start()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void ImGuiLayer::End()
  {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::GetInstance();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }

  void ImGuiLayer::Destroy()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }
}