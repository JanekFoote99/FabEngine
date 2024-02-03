#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <iostream>

bool loadOBJ(
	const char* filepath,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
);
