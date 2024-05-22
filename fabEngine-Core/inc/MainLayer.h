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