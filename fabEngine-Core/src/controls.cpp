#include "../inc/controls.h"

// Initial position : on +Z
glm::vec3 position = glm::vec3(2.0f, 2.0f, 7.0f);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
int FOV = 45.0f;

float speed = 5.0f; // 3 units / second
float mouseSpeed = 2.0f;

// Direction of Mouse scroll
int mouseScrollDirection = 0;

// Variables to keep track of persisted mouse scroll
bool mWheelActive = false;
int frameCountMWheel = 0;

// TODO: Implement Camera movement within Keycallback
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void scrollCallback(GLFWwindow* window, double x, double y)
{
	// set mouse scroll direction (up/down)
	mouseScrollDirection = y;

	// Set timer on mouse wheel up and down to make the scrolling persist longer
	mWheelActive = true;
	frameCountMWheel = 0;
}

//TODO: disable camera movement when cursor is hovering over UI
void generateMatricesFromInputs(GLFWwindow* window, glm::mat4& ViewMatrix, glm::mat4& ProjectionMatrix, glm::f32 nearPlane, glm::f32 farPlane, bool movementEnabled)
{
	// Compute delta between two frames
	static double prevTime = glfwGetTime();
	double curTime = glfwGetTime();
	float deltaTime = float(curTime - prevTime);

	// Mouse Position
	double xPos, yPos;
	static double prevXPos, prevYPos;
	
	// Get the current Mouse position and store it in xPos and yPos
	glfwGetCursorPos(window, &xPos, &yPos);

	if (!movementEnabled)
	{
			prevTime = curTime;
			prevXPos = xPos;
			prevYPos = yPos;
			return;
	}
	else
	{
			// Current Window Size
			int windowWidth;
			int windowHeight;

			// Get the current window Width and Height and store it in windowWidth and windowHeight
			glfwGetWindowSize(window, &windowWidth, &windowHeight);

			// Compute the delta between the last and the current Mouse position
			float deltaX = prevXPos - xPos;
			float deltaY = prevYPos - yPos;

			// Compute the delta distance in each direction between the last and the current frame
			horizontalAngle += mouseSpeed * deltaTime * deltaX;
			verticalAngle += mouseSpeed * deltaTime * deltaY;

			// Direction : Spherical coordinates to Cartesian coordinates conversion
			glm::vec3 direction(
					cos(verticalAngle) * sin(horizontalAngle),
					sin(verticalAngle),
					cos(verticalAngle) * cos(horizontalAngle)
			);

			// Right vector
			glm::vec3 right = glm::vec3(
					sin(horizontalAngle - 3.14f / 2.0f),
					0,
					cos(horizontalAngle - 3.14f / 2.0f)
			);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			// Move forward
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				position += direction * deltaTime * speed;
			}
			// Move backward
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				position -= direction * deltaTime * speed;
			}
			// Strafe right
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				position += right * deltaTime * speed;
			}
			// Strafe left
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				position -= right * deltaTime * speed;
			}
			// Move up
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				position.y += 0.001f;
			}
			// Move down
			if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			{
				position.y -= 0.001f;
			}
			// TODO: Faster Camera movement after pressing shift
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			{
				speed == 10.0f;
			}
			else
			{
				speed == 5.0f;
			}

			glfwSetScrollCallback(window, scrollCallback);

			// TODO: Verschachtelung auflösen
			// make 5 iterations of a mouse scroll to make the experience more smoothly
			if (mWheelActive)
			{
					frameCountMWheel++;
					if (frameCountMWheel >= 5)
					{
							frameCountMWheel = 0;
							mWheelActive = false;
							mouseScrollDirection = 0;
					}
			}
			// TODO END
			FOV = FOV - 5 * mouseScrollDirection;

			FOV = std::clamp(FOV, 30, 150);

			ProjectionMatrix = glm::perspective(glm::radians(static_cast<float>(FOV)), 4.0f / 3.0f, nearPlane, farPlane);
			// Camera matrix
			ViewMatrix = glm::lookAt(
					position,           // Camera is here
					position + direction, // and looks here : at the same position, plus "direction"
					up                  // Head is up (set to 0,-1,0 to look upside-down)
			);

			prevTime = curTime;
			prevXPos = xPos;
			prevYPos = yPos;
	}
}

void rotateObject(GLFWwindow* window, glm::mat4& modelMatrix)
{
			// Compute delta between two frames
	static double prevTime = glfwGetTime();
	double curTime = glfwGetTime();
	float deltaTime = float(curTime - prevTime);

	// Mouse Position
	double xPos, yPos;
	static double prevXPos, prevYPos;

	// Get the current Mouse position and store it in xPos and yPos
	glfwGetCursorPos(window, &xPos, &yPos);

	// Current Window Size
	int windowWidth;
	int windowHeight;

	// Get the current window Width and Height and store it in windowWidth and windowHeight
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	// Compute the delta between the last and the current Mouse position
	float deltaX = prevXPos - xPos;
	float deltaY = prevYPos - yPos;

	// Compute the delta distance in each direction between the last and the current frame
	horizontalAngle += mouseSpeed * deltaTime * deltaX;
	verticalAngle += mouseSpeed * deltaTime * deltaY;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector : perpendicular to both direction and right
	glm::vec3 up = glm::cross(right, direction);
}