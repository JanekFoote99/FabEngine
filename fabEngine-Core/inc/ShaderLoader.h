#pragma once

#include <iostream>
#include <string>

#include <sstream>
#include <fstream>

#include <vector>
#include <glad/glad.h>

class ShaderLoader
{
public:
  static GLuint LoadShader(const char* vertexPath, const char* fragPath);

private:

};

