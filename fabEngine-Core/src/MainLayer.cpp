#include "MainLayer.h"

#include "ShaderLoader.h"
#include "MeshViewer.h"
#include <glm/gtx/string_cast.hpp>

MainLayer::MainLayer()
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
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	//Setup Vertax Array Object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Create and Bind Shaders
	GLuint shaderID = ShaderLoader::LoadShader("shader/vertShader.glsl", "shader/fragShader.glsl");

	setUniformLocations(shaderID);

	// initialize light object and set its position and vertexBuffer
	Light light;
	light.vertexBuffer = { glm::vec3(-0.5f, -0.5f, 0.5f),
								 glm::vec3(0.5f, -0.5f, 0.5f),
								 glm::vec3(0.5f, 0.5f, 0.5f),
								 glm::vec3(-0.5f, 0.5f, 0.5f),
								 glm::vec3(-0.5f, -0.5f, -0.5f),
								 glm::vec3(0.5f, -0.5f, -0.5f),
								 glm::vec3(0.5f, 0.5f, -0.5f),
								 glm::vec3(-0.5f, 0.5f, -0.5f) };
	// Create the index buffer for the cube
	light.indexBuffer = { glm::vec3(0, 1, 2),
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
	// Accept fragment if it closer to the camera than the former one (z-culling)
	glDepthFunc(GL_LESS);

	const char* filepath = "Assets/suzanne.obj";
	const char* texturePath = "Assets/suzanneUV.DDS";

	// Setup Meshviewer
	MeshViewer mesh(filepath, texturePath);

	// Initializing transformation Matrices
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	float framerate = 0.0f;
	std::string MVPString = glm::to_string(glm::mat4(1.0f));

	generateMatricesFromInputs(window, viewMatrix, projectionMatrix, imGuiAttributes.nearPlane, imGuiAttributes.farPlane, true);

	bool movementEnabled = false;
}

void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(float time)
{
}

void MainLayer::OnImGuiRender()
{
	//// Display Framerate
	//ImGui::Begin("Display Framerate", open_ptr, transparentTextFlags);
	//ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	//ImGui::Text("%.0f", framerate);
	//ImGui::PopStyleColor();
	//ImGui::End();

	//// Display current camera position
	//ImGui::Begin("Camera");
	//ImGui::IsWindowHovered(movementEnabled);
	//ImGui::Text("X: %.2f", position.x);
	//ImGui::Text("Y: %.2f", position.y);
	//ImGui::Text("Z: %.2f", position.z);
	//ImGui::End();


	//// Configuration Window for lighting attributes
	//ImGui::Begin("Lighting Configuration");
	//ImGui::SliderFloat("Near Plane", &imGuiAttributes.nearPlane, 0.0f, 10.0f);
	//ImGui::SliderFloat("Far Plane", &imGuiAttributes.farPlane, 10.0f, 100.0f);
	//ImGui::Text("Light Position");
	//ImGui::SliderFloat("X", &LightPosition.x, -30.0f, 30.0f);
	//ImGui::SliderFloat("Y", &LightPosition.y, -30.0f, 30.0f);
	//ImGui::SliderFloat("Z", &LightPosition.z, -30.0f, 30.0f);
	//ImGui::ColorPicker3("Ambient Color", &imGuiAttributes.ambientColor[0]);
	//ImGui::ColorPicker3("Diffuse Color", &imGuiAttributes.diffuseColor[0]);
	//ImGui::ColorPicker3("Specular Color", &imGuiAttributes.specularColor[0]);
	//ImGui::SliderFloat("Specular Exponent", &imGuiAttributes.specularExponent, 0.0f, 100.0f);
	//ImGui::End();

	////TODO: Make menu bar for all kind of configurations

	//// Display MVP Matrix
	//ImGui::Begin("MVP Matrix");
	//ImGui::Text(MVPString.c_str());
	//ImGui::End();

	//// Settings window
	//ImGui::Begin("Settings");
	//ImGui::Checkbox("Rotate Object", &imGuiAttributes.rotateObjectEnabled);
	//ImGui::Checkbox("Display Bounding Box", &imGuiAttributes.displayBoundingBox);
	//ImGui::End();
}

