#pragma once
#include <string>

#include "ImageLoader.h"
#include "OBJLoader.h"

#include <vector>
#include "glm/glm.hpp"


// TODO: Create ComputeWireframe and DrawWireframe methods
class MeshViewer
{
public:
  MeshViewer();
  MeshViewer(const char* filepath);
  MeshViewer(const char* filepath, const char* texturePath);
  ~MeshViewer();

  void ComputeBoundingBox();
  void Clean();
  void RenderMesh();
  void RenderBoundingBox();
private:
  const char* m_filepath;
  const char* m_texturePath;

  bool m_ObjLoaded;
  bool m_enableBoundingBox;
  std::vector<glm::vec3> m_boundingBoxVertices;
  std::vector<unsigned int> m_boundingBoxIndices;

  std::vector<glm::vec3> m_vertices;
  std::vector<unsigned int> m_indices;
  std::vector<glm::vec3> m_normals;
  std::vector<glm::vec2> m_uvs;
};

