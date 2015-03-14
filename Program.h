#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.

#include "Shader.h"
#include "glLog.h"

class Program
{
public:
	Program(Shader vertexShader, Shader fragmentShader);
	void use();
	int getUniform(const char* name);

private:
	Shader vertex;
	Shader fragment;
	GLuint shader_program;
};