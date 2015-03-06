#include "Program.h"

Program::Program(Shader vertexShader, Shader fragmentShader)
{
	vertex = vertexShader;
	fragment = fragmentShader;

	//Are we seriously making a program inside of a program?
	shader_program = glCreateProgram();
	glAttachShader(shader_program, fragment.getShader());
	glAttachShader(shader_program, vertex.getShader());
	glLinkProgram(shader_program);
}

void Program::use()
{
	glUseProgram(shader_program);
}