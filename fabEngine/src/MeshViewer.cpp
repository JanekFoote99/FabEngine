#include "../include/MeshViewer.h"

//TODO: Setup default constructor and destructor
MeshViewer::MeshViewer()
{
  
}

MeshViewer::~MeshViewer()
{

}

MeshViewer::MeshViewer(const char* filepath, const char* texturePath) : m_filepath(filepath), m_texturePath(texturePath)
{
  m_ObjLoaded = loadOBJ(filepath, m_vertices, m_uvs, m_normals);
  GLuint texture = ImageLoader::loadDDS(texturePath);
  ComputeBoundingBox();
}

MeshViewer::MeshViewer(const char* filepath) : m_filepath(filepath)
{
  m_ObjLoaded = loadOBJ(filepath, m_vertices, m_uvs, m_normals);
  ComputeBoundingBox();
}

void MeshViewer::Clean()
{
  m_vertices.clear();
  m_uvs.clear();
  m_normals.clear();
  m_indices.clear();
}

void MeshViewer::RenderMesh()
{
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

  GLuint uvBuffer{};
  if(!m_uvs.empty())
  {
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0], GL_STATIC_DRAW);
  }
  
  GLuint normalBuffer{};
  if (!m_normals.empty())
  {
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
  }

  GLuint indexBuffer{};
  if (!m_indices.empty())
  {
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
  }


  // Send Vertex Attribute Data to Shaders
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(
    0,                                // attribute
    3,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0								  // array buffer offset
  );

  if (!m_uvs.empty())
  {
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(
      1,                                // attribute
      2,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0								  // array buffer offset
    );
  }

  if (!m_normals.empty())
  {
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(
      2,                                // attribute
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0								  // array buffer offset
    );
  }

  if (!m_indices.empty())
  {
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glVertexAttribPointer(
      1,                                // attribute
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0								  // array buffer offset
    );
  }


  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

  // Freigabe der Buffer
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &uvBuffer);
  glDeleteBuffers(1, &normalBuffer);
  glDeleteBuffers(1, &indexBuffer);
  //glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}

void MeshViewer::RenderBoundingBox()
{
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, m_boundingBoxVertices.size() * sizeof(glm::vec3), &m_boundingBoxVertices[0], GL_STATIC_DRAW);


  GLuint indexBuffer{};
  if (!m_indices.empty())
  {
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_boundingBoxIndices.size() * sizeof(unsigned int), &m_boundingBoxIndices[0], GL_STATIC_DRAW);
  }


  // Send Vertex Attribute Data to Shaders
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(
    0,                                // attribute
    3,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0								  // array buffer offset
  );

  if (!m_boundingBoxIndices.empty())
  {
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glVertexAttribPointer(
      1,                                // attribute
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0								  // array buffer offset
    );
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glDrawElements(GL_LINES, m_boundingBoxIndices.size(), GL_UNSIGNED_INT, &m_boundingBoxIndices[0]);

  // Freigabe der Buffer
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);
}

void MeshViewer::ComputeBoundingBox()
{
  float minX = m_vertices[0].x, minY = m_vertices[0].y, minZ = m_vertices[0].z;
  float maxX = m_vertices[0].x, maxY = m_vertices[0].y, maxZ = m_vertices[0].z;

  for(int i = 0; i < m_vertices.size(); i++)
  {
    if(m_vertices[i].x < minX) minX = m_vertices[i].x;
    if(m_vertices[i].x > maxX) maxX = m_vertices[i].x;
    if(m_vertices[i].y < minY) minY = m_vertices[i].y;
    if(m_vertices[i].y > maxY) maxY = m_vertices[i].y;
    if(m_vertices[i].z < minZ) minZ = m_vertices[i].z;
    if(m_vertices[i].z > maxZ) maxZ = m_vertices[i].z;
  }

  //Create the bounding box vertices and            indices 
  m_boundingBoxVertices = {
    glm::vec3(minX, minY, minZ), // back lower left    0
    glm::vec3(minX, minY, maxZ), // front lower left   1
    glm::vec3(minX, maxY, minZ), // back upper left    2
    glm::vec3(minX, maxY, maxZ), // front upper left   3
    glm::vec3(maxX, minY, minZ), // back lower right   4
    glm::vec3(maxX, minY, maxZ), // front lower right  5
    glm::vec3(maxX, maxY, minZ), // back upper right   6
    glm::vec3(maxX, maxY, maxZ)  // front upper right  7
  };

  //m_boundingBoxIndices = {
  //  0, 1, 2, 1, 2, 3, // left wall
  //  4, 5, 6, 5, 6, 7, // right wall
  //  0, 2, 4, 2, 4, 6, // back wall
  //  1, 3, 5, 3, 5, 7, // front wall
  //  2, 3, 6, 3, 6, 7, // top wall
  //  0, 1, 4, 1, 4, 5  // bottom wall
  //};

  m_boundingBoxIndices = {
    0, 1, 1, 3, 3, 2, 2, 0, // bottom face
    4, 5, 5, 7, 7, 6, 6, 4, // top face
    0, 4, 1, 5, 2, 6, 3, 7  // connecting lines
  };
}