#pragma once

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"


namespace fabCoreGL
{
  class ImGuiLayer
  {
  public:
    ImGuiLayer();

    void Init();
    void Destroy();

    void Start();
    void End();
  private:

  };
}