#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.

#include "Shader.h"

class Program
{
public:
	Program(Shader vertexShader, Shader fragmentShader);
	void use();

private:
	Shader vertex;
	Shader fragment;
	GLuint shader_program;
};