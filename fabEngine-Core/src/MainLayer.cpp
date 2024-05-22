#include "MainLayer.h"

#include "ShaderLoader.h"

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
}

void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(float time)
{
}

void MainLayer::OnImGuiRender()
{

}

