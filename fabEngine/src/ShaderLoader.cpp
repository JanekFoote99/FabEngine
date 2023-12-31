#include "../inc/ShaderLoader.h"

GLuint ShaderLoader::LoadShader(const char* vertexPath, const char* fragPath)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexPath, std::ios::in);

	if (vertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else
	{
		std::cout << "Can't open " << vertexPath << ". Possibly in the wrong directory.\n";
		return 0;
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragPath, std::ios::in);

	if (fragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}
	else
	{
		std::cout << "Can't open " << fragPath << ". Possibly in the wrong directory.\n";
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	//Compilation: Vertex Shader
	std::cout << "Compiling shader: " << vertexPath << ".\n";
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Status: Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		std::cout << &vertexShaderErrorMessage[0];
	}

	//Compilation: Fragment Shader
	std::cout << "Compiling shader : " << fragPath << ".\n";
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Status: Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		std::cout << &fragmentShaderErrorMessage[0];
	}

	//Link the program
	std::cout << "Linking program\n";
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check Program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << &programErrorMessage[0];
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}