#include "../include/OBJLoader.h"

bool loadOBJ(
	const char* filepath,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
)
{
	std::cout << "Loading OBJ File: " << filepath << std::endl;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE* file;
	if (fopen_s(&file, filepath, "rb") != 0)
	{
		std::cout << "Error loading File " << filepath << std::endl;
		return false;
	}

	while (true)
	{
		char lineHeader[128];

		int res = fscanf_s(file, "%s", lineHeader, (unsigned int)sizeof(lineHeader));

		if (res == EOF)
			break;

		//check if lineHeader is zero terminated
		if (lineHeader[0] == '\0')
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 curVertex;
			fscanf_s(file, "%f %f %f\n", &curVertex.x, &curVertex.y, &curVertex.z);
			temp_vertices.push_back(curVertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 curUv;
			fscanf_s(file, "%f %f\n", &curUv.x, &curUv.y);
			temp_uvs.push_back(curUv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 curNormal;
			fscanf_s(file, "%f %f %f\n", &curNormal.x, &curNormal.y, &curNormal.z);
			temp_normals.push_back(curNormal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
						 &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
						 &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
						 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				std::cout << "File can't be read by parser\n";
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}
	fclose(file);
	return true;
}
