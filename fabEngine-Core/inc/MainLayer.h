#pragma once

#include <vector>
#include "Layer.h"
#include "types.h"
#include <GLCore.h>

using namespace fabTypes;
using namespace fabCoreGL;

class MainLayer : public Layer
{
public:
  struct Light
  {
    std::vector<f32v3> vertexBuffer;
    std::vector<f32v3> indexBuffer;
    std::vector<f32v3> colorBuffer;
    f32v3 position = f32v3(5.0f, 4.0f, 4.0f);
    f32v3 color = f32v3(0.0f, 0.0f, 0.0f);
  };

  MainLayer();
  virtual ~MainLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float time) override;
  void OnImGuiRender() override;
private:
  std::vector<f32v3> m_vertexBuffer;
  std::vector<ui32> m_indexBuffer;

  GLuint m_vao, m_vbo;
};