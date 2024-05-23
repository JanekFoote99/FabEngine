#include <iostream>
#include <iomanip>

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//#define IMGUI_IMPL_OPENGL_LOADER_GLAD
//#include "imgui.h"
//#include "examples/imgui_impl_glfw.h"
//#include "examples/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include <time.h>

#include <ImGuiLayer.h>
#include <Application.h>

#include "../inc/objloader.h"
#include "../inc/ShaderLoader.h"
#include "../inc/ImageLoader.h"
#include "../inc/controls.h"
#include "../inc/MeshViewer.h"

glm::mat4 MVPMatrix;
glm::mat4 MVInvTrans;
f32v3 LightPosition;

using namespace fabCoreGL;

// make a struct of a light source containing vertex buffer, index buffer, position, and color
struct Light
{
	std::vector<f32v3> vertexBuffer;
	std::vector<f32v3> indexBuffer;
	std::vector<f32v3> colorBuffer;
	f32v3 position = f32v3(5.0f, 4.0f, 4.0f);
	f32v3 color = f32v3(0.0f, 0.0f, 0.0f);
};

struct ImGuiAttributes
{
	glm::f32 nearPlane = 0.1f;
	glm::f32 farPlane = 100.0f;

	f32v3 ambientColor = f32v3(0.0f, 0.0f, 0.0f);
	f32v3 diffuseColor = f32v3(1.0f, 1.0f, 1.0f);
	f32v3 specularColor = f32v3(1.0f, 1.0f, 1.0f);
	float specularExponent = 64.0f;

	bool rotateObjectEnabled = false;
	bool displayBoundingBox = false;
};

std::string Mat4ToString(glm::mat4 MVP)
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(2);

	const float* matrixData = glm::value_ptr(MVP);

	oss << "[" << matrixData[0] << ", " << matrixData[1] << ", " << matrixData[2] << ", " << matrixData[3] << "]\n";
	oss << "[" << matrixData[4] << ", " << matrixData[5] << ", " << matrixData[6] << ", " << matrixData[7] << "]\n";
	oss << "[" << matrixData[8] << ", " << matrixData[9] << ", " << matrixData[10] << ", " << matrixData[11] << "]\n";
	oss << "[" << matrixData[12] << ", " << matrixData[13] << ", " << matrixData[14] << ", " << matrixData[15] << "]";


	return oss.str();
}

int main()
{
	fabCoreGL::Application app("fabCore", 1920, 1080);

	ImGuiAttributes imGuiAttributes;

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	//Setup Vertax Array Object
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = ShaderLoader::LoadShader("shader/vertShader.glsl", "shader/fragShader.glsl");

	GLuint ModelID = glGetUniformLocation(programID, "modelMatrix");
	GLuint ViewID = glGetUniformLocation(programID, "viewMatrix");
	GLuint ProjectionID = glGetUniformLocation(programID, "projectionMatrix");
	GLuint TimerID = glGetUniformLocation(programID, "timer");
	GLuint SamplerID = glGetUniformLocation(programID, "textureSampler");
	GLuint LightID = glGetUniformLocation(programID, "lightPos");
	GLuint ambientColorID = glGetUniformLocation(programID, "ambientColor");
	GLuint diffuseColorID = glGetUniformLocation(programID, "diffuseColor");
	GLuint specularColorID = glGetUniformLocation(programID, "specularColor");
	GLuint specularExponentID = glGetUniformLocation(programID, "specularExponent");
	GLuint MVInvTransID = glGetUniformLocation(programID, "MVInvTrans");

	// initialize light object and set its position and vertexBuffer
	Light light;
	light.vertexBuffer = { f32v3(-0.5f, -0.5f, 0.5f),
								 f32v3(0.5f, -0.5f, 0.5f),
								 f32v3(0.5f, 0.5f, 0.5f),
								 f32v3(-0.5f, 0.5f, 0.5f),
								 f32v3(-0.5f, -0.5f, -0.5f),
								 f32v3(0.5f, -0.5f, -0.5f),
								 f32v3(0.5f, 0.5f, -0.5f),
								 f32v3(-0.5f, 0.5f, -0.5f) };
	// Create the index buffer for the cube
	light.indexBuffer = { f32v3(0, 1, 2),
								 f32v3(0, 2, 3),
								 f32v3(1, 5, 6),
								 f32v3(1, 6, 2),
								 f32v3(7, 6, 5),
								 f32v3(7, 5, 4),
								 f32v3(4, 0, 3),
								 f32v3(4, 3, 7),
								 f32v3(4, 5, 1),
								 f32v3(4, 1, 0),
								 f32v3(3, 2, 6),
								 f32v3(3, 6, 7) };

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Enable Backface Culling
	glEnable(GL_CULL_FACE);
	// Accept fragment if it closer to the camera than the former one (z-culling)
	glDepthFunc(GL_LESS);

	LightPosition = f32v3(-10.0f, 5.0f, 5.0f);

	const char* filepath = "Assets/suzanne.obj";
	const char* texturePath = "Assets/suzanneUV.DDS";

	// Setup Meshviewer
	MeshViewer mesh(filepath, texturePath);

	// Initializing transformation Matrices
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	glm::f64 prevTime = glfwGetTime();
	glm::i32 frameCount = 0;

	float framerate = 0.0f;
	std::string MVPString = glm::to_string(glm::mat4(1.0f));

	GLFWwindow* window = app.GetWindow().GetWindow();

	generateMatricesFromInputs(window, viewMatrix, projectionMatrix, imGuiAttributes.nearPlane, imGuiAttributes.farPlane, true);

	bool movementEnabled = false;

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//use shaders
		glUseProgram(programID);

		// Debugging breakpoint
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			int adf = 3;
		}

		glm::f32 timer = glm::f32(frameCount) / 600.0f;


		/*if (ImGui::IsWindowHovered(ImGuiHoveredFlags(1)))
		{
			std::cout << "Window is Hovered" << std::endl;
		}*/

		// Set the input mode to show the cursor as long as left mouse button is pressed
		/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		} 
		else
		{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				std::cout << "Cursor is normal" << std::endl;
		}*/

		// Cursor is shown all the time
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				movementEnabled = true;
		else
				movementEnabled = false;

		generateMatricesFromInputs(window, viewMatrix, projectionMatrix, imGuiAttributes.nearPlane, imGuiAttributes.farPlane, movementEnabled);

		// Creating the full transformation matrix
		MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;
		MVInvTrans = viewMatrix * modelMatrix;

		MVPString = Mat4ToString(MVPMatrix);

		mesh.RenderMesh();
		if (imGuiAttributes.displayBoundingBox)
		{
			mesh.RenderBoundingBox();
		}

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

		if (ImGui::IsWindowHovered(0))
		{
			std::cout << "Window is hovered by mouse" << std::endl;
		}

		//// Vertices
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		//glVertexAttribPointer(
		//	0,
		//	3,
		//	GL_FLOAT,
		//	GL_FALSE,
		//	0,
		//	0
		//);

		//// UV Coordinates
		//glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		//glVertexAttribPointer(
		//	1,                                // attribute
		//	2,                                // size
		//	GL_FLOAT,                         // type
		//	GL_FALSE,                         // normalized?
		//	0,                                // stride
		//	0								  // array buffer offset
		//);

		//// Normals
		//glEnableVertexAttribArray(2);
		//glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		//glVertexAttribPointer(
		//	2,                                // attribute
		//	3,                                // size
		//	GL_FLOAT,                         // type
		//	GL_FALSE,                         // normalized?
		//	0,                                // stride
		//	0								  // array buffer offset
		//);

		//// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // 3 indices starting at 0 -> 1 triangle

		framerate = ImGui::GetIO().Framerate;

		// Define flags for the transparent FPS display
		ImGuiWindowFlags transparentTextFlags = 0;
		transparentTextFlags |= ImGuiWindowFlags_NoBackground;
		transparentTextFlags |= ImGuiWindowFlags_NoTitleBar;
		transparentTextFlags |= ImGuiWindowFlags_NoResize;
		transparentTextFlags |= ImGuiWindowFlags_NoMove;

		bool value = true;
		bool* open_ptr = &value;

		/// Display Framerate
		ImGui::Begin("Display Framerate", open_ptr, transparentTextFlags);
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
		ImGui::Text("%.0f", framerate);
		ImGui::PopStyleColor();
		ImGui::End();

		// Display current camera position
		ImGui::Begin("Camera");
		ImGui::IsWindowHovered(movementEnabled);
		ImGui::Text("X: %.2f", position.x);
		ImGui::Text("Y: %.2f", position.y);
		ImGui::Text("Z: %.2f", position.z);
		ImGui::End();


		// Configuration Window for lighting attributes
		ImGui::Begin("Lighting Configuration");
		ImGui::SliderFloat("Near Plane", &imGuiAttributes.nearPlane, 0.0f, 10.0f);
		ImGui::SliderFloat("Far Plane", &imGuiAttributes.farPlane, 10.0f, 100.0f);
		ImGui::Text("Light Position");
		ImGui::SliderFloat("X", &LightPosition.x, -30.0f, 30.0f);
		ImGui::SliderFloat("Y", &LightPosition.y, -30.0f, 30.0f);
		ImGui::SliderFloat("Z", &LightPosition.z, -30.0f, 30.0f);
		ImGui::ColorPicker3("Ambient Color", &imGuiAttributes.ambientColor[0]);
		ImGui::ColorPicker3("Diffuse Color", &imGuiAttributes.diffuseColor[0]);
		ImGui::ColorPicker3("Specular Color", &imGuiAttributes.specularColor[0]);
		ImGui::SliderFloat("Specular Exponent", &imGuiAttributes.specularExponent, 0.0f, 100.0f);
		ImGui::End();

		//TODO: Make menu bar for all kind of configurations

		// Display MVP Matrix
		ImGui::Begin("MVP Matrix");
		ImGui::Text(MVPString.c_str());
		ImGui::End();

		// Settings window
		ImGui::Begin("Settings");
		ImGui::Checkbox("Rotate Object", &imGuiAttributes.rotateObjectEnabled);
		ImGui::Checkbox("Display Bounding Box", &imGuiAttributes.displayBoundingBox);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	//clean VertexBufferObject (vbo)
	/*glDeleteBuffers(1, &vertexBuffer);*/
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	//close Window
	glfwTerminate();

	return 0;
}