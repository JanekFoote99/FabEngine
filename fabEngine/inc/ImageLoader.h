#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include "GL/glew.h"

namespace ImageLoader
{
	GLuint loadBMP(const char* filepath);
	GLuint loadDDS(const char* filepath);


	extern unsigned char m_header[54];
	extern unsigned int m_dataPos;
	extern unsigned int m_width, m_height;
	extern unsigned int m_imageSize;
	//RGB data
	extern unsigned char* m_data;
};

