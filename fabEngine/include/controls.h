#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>
#include <cstdint>
#include <iomanip>

#include "GLFW/glfw3.h"

#include <iostream>

extern glm::vec3 position;

void generateMatricesFromInputs(GLFWwindow* window, glm::mat4& ViewMatrix, glm::mat4& ProjectionMatrix, glm::f32 nearPlane, glm::f32 farPlane, bool movementEnabled);
void rotateObject(GLFWwindow* window, glm::mat4& modelMatrix);

