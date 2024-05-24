#pragma once

#include <vector>
#include "Layer.h"
#include "types.h"
#include <GLCore.h>
#include "CameraController.h"

using namespace fabTypes;
using namespace fabCoreGL;

struct Light
{
  std::vector<f32v3> vertexBuffer;
  std::vector<f32v3> indexBuffer;
  std::vector<f32v3> colorBuffer;
  f32v3 position = f32v3(5.0f, 4.0f, 4.0f);
  f32v3 color = f32v3(0.0f, 0.0f, 0.0f);
};

struct GuiAttributes
{
  f32v4 backgroundColor = f32v4(0.3f, 0.3f, 0.3f, 0.0f);

  glm::f32 nearPlane = 0.1f;
  glm::f32 farPlane = 100.0f;

  f32v3 ambientColor = f32v3(0.0f, 0.0f, 0.0f);
  f32v3 diffuseColor = f32v3(1.0f, 1.0f, 1.0f);
  f32v3 specularColor = f32v3(1.0f, 1.0f, 1.0f);
  float specularExponent = 64.0f;

  f32 frameTime = 0.0f;

  bool rotateObjectEnabled = false;
  bool displayBoundingBox = false;
};

class MainLayer : public Layer
{
public:

  MainLayer();
  virtual ~MainLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float time) override;
  void OnImGuiRender() override;

  void UpdateUniforms();
private:
  CameraController m_controller;
  std::vector<f32v3> m_vertexBuffer;
  std::vector<ui32> m_indexBuffer;
  GuiAttributes m_GuiAttributes;

  Light m_light;
  GLuint m_vao;
};