#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include "glLog.h"

class Shader
{
public:
	Shader();
	Shader(const char* fileName, GLuint shaderType);
	GLuint getShader();

private:
	GLuint shader;
};