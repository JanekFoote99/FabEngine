#include "MainLayer.h"

#include "ShaderLoader.h"
#include "MeshViewer.h"
#include <glm/gtx/string_cast.hpp>

MainLayer::MainLayer() :
  m_controller()
{

}

MainLayer::~MainLayer()
{

}

void setUniformLocations(GLuint& shaderID)
{
  GLuint ModelID = glGetUniformLocation(shaderID, "modelMatrix");
  GLuint ViewID = glGetUniformLocation(shaderID, "viewMatrix");
  GLuint ProjectionID = glGetUniformLocation(shaderID, "projectionMatrix");
  GLuint TimerID = glGetUniformLocation(shaderID, "timer");
  GLuint SamplerID = glGetUniformLocation(shaderID, "textureSampler");
  GLuint LightID = glGetUniformLocation(shaderID, "lightPos");
  GLuint ambientColorID = glGetUniformLocation(shaderID, "ambientColor");
  GLuint diffuseColorID = glGetUniformLocation(shaderID, "diffuseColor");
  GLuint specularColorID = glGetUniformLocation(shaderID, "specularColor");
  GLuint specularExponentID = glGetUniformLocation(shaderID, "specularExponent");
  GLuint MVInvTransID = glGetUniformLocation(shaderID, "MVInvTrans");
}

void MainLayer::OnAttach()
{
  glClearColor(m_GuiAttributes.backgroundColor.x,
    m_GuiAttributes.backgroundColor.y,
    m_GuiAttributes.backgroundColor.z,
    m_GuiAttributes.backgroundColor.w);

  //Setup Vertax Array Object
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Create and Bind Shaders
  GLuint shaderID = ShaderLoader::LoadShader("shader/vertShader.glsl", "shader/fragShader.glsl");

  setUniformLocations(shaderID);

  // initialize light object and set its position and vertexBuffer
  m_light.vertexBuffer = { glm::vec3(-0.5f, -0.5f, 0.5f),
                 glm::vec3(0.5f, -0.5f, 0.5f),
                 glm::vec3(0.5f, 0.5f, 0.5f),
                 glm::vec3(-0.5f, 0.5f, 0.5f),
                 glm::vec3(-0.5f, -0.5f, -0.5f),
                 glm::vec3(0.5f, -0.5f, -0.5f),
                 glm::vec3(0.5f, 0.5f, -0.5f),
                 glm::vec3(-0.5f, 0.5f, -0.5f) };

  // Create the index buffer for the light cube
  m_light.indexBuffer = { glm::vec3(0, 1, 2),
                 glm::vec3(0, 2, 3),
                 glm::vec3(1, 5, 6),
                 glm::vec3(1, 6, 2),
                 glm::vec3(7, 6, 5),
                 glm::vec3(7, 5, 4),
                 glm::vec3(4, 0, 3),
                 glm::vec3(4, 3, 7),
                 glm::vec3(4, 5, 1),
                 glm::vec3(4, 1, 0),
                 glm::vec3(3, 2, 6),
                 glm::vec3(3, 6, 7) };

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Enable Backface Culling
  glEnable(GL_CULL_FACE);
  // Enable Z-Culling
  glDepthFunc(GL_LESS);

  const char* filepath = "Assets/suzanne.obj";
  const char* texturePath = "Assets/suzanneUV.DDS";

  // Setup Meshviewer
  MeshViewer mesh(filepath, texturePath);

  mesh.RenderMesh();

  UpdateUniforms();
}

void MainLayer::OnDetach()
{
  // TODO: Delete OpenGL-Buffers
}

void MainLayer::OnUpdate(float time)
{
  m_controller.OnUpdate(time);

  m_GuiAttributes.frameTime = time;

  glm::mat4 modelMatrix = f32m4(1.0f);
  glm::mat4 viewMatrix = m_controller.GetCamera().GetViewMatrix();
  glm::mat4 projectionMatrix = m_controller.GetCamera().GetProjectionMatrix();
}

void MainLayer::OnImGuiRender()
{
  // Display Framerate
  ImGui::Begin("Display Framerate");
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
  ImGui::Text("%.0f", m_GuiAttributes.frameTime);
  ImGui::PopStyleColor();
  ImGui::End();

  // Display current camera position
  ImGui::Begin("Camera");
  ImGui::Text("X: %.2f", m_controller.GetCameraPosition().x);
  ImGui::Text("Y: %.2f", m_controller.GetCameraPosition().y);
  ImGui::Text("Z: %.2f", m_controller.GetCameraPosition().z);
  ImGui::End();


  // Configuration Window for lighting attributes
  ImGui::Begin("Lighting Configuration");
  ImGui::SliderFloat("Near Plane", &m_GuiAttributes.nearPlane, 0.0f, 10.0f);
  ImGui::SliderFloat("Far Plane", &m_GuiAttributes.farPlane, 10.0f, 100.0f);
  ImGui::Text("Light Position");
  ImGui::SliderFloat("X", &m_light.position.x, -30.0f, 30.0f);
  ImGui::SliderFloat("Y", &m_light.position.y, -30.0f, 30.0f);
  ImGui::SliderFloat("Z", &m_light.position.z, -30.0f, 30.0f);
  ImGui::ColorPicker3("Ambient Color", &m_GuiAttributes.ambientColor[0]);
  ImGui::ColorPicker3("Diffuse Color", &m_GuiAttributes.diffuseColor[0]);
  ImGui::ColorPicker3("Specular Color", &m_GuiAttributes.specularColor[0]);
  ImGui::SliderFloat("Specular Exponent", &m_GuiAttributes.specularExponent, 0.0f, 100.0f);
  ImGui::End();

  // Settings window
  ImGui::Begin("Settings");
  ImGui::Checkbox("Rotate Object", &m_GuiAttributes.rotateObjectEnabled);
  ImGui::Checkbox("Display Bounding Box", &m_GuiAttributes.displayBoundingBox);
  ImGui::End();
}

void MainLayer::UpdateUniforms()
{
  // Send Matrix data to Shader
  glUniformMatrix4fv(ModelID, 1, GL_FALSE, &modelMatrix[0][0]);
  glUniformMatrix4fv(ViewID, 1, GL_FALSE, &viewMatrix[0][0]);
  glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
  glUniformMatrix4fv(MVInvTransID, 1, GL_FALSE, &MVInvTrans[0][0]);
  glUniform1f(TimerID, timer);

  // Send Light data to Shader
  glUniform3f(LightID, LightPosition.x, LightPosition.y, LightPosition.z);
  glUniform3f(ambientColorID, imGuiAttributes.ambientColor.x, imGuiAttributes.ambientColor.y, imGuiAttributes.ambientColor.z);
  glUniform3f(diffuseColorID, imGuiAttributes.diffuseColor.x, imGuiAttributes.diffuseColor.y, imGuiAttributes.diffuseColor.z);
  glUniform3f(specularColorID, imGuiAttributes.specularColor.x, imGuiAttributes.specularColor.y, imGuiAttributes.specularColor.z);
  glUniform1f(specularExponentID, imGuiAttributes.specularExponent);
}
