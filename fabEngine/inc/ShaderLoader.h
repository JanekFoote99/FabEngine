#pragma once
#include "GL/glew.h"
#include <iostream>
#include <string>

#include <sstream>
#include <fstream>

#include <vector>


class ShaderLoader
{
public:
  static GLuint LoadShader(const char* vertexPath, const char* fragPath);

private:

};

