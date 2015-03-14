#include "Program.h"

Program::Program(Shader vertexShader, Shader fragmentShader)
{
	vertex = vertexShader;
	fragment = fragmentShader;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, fragment.getShader());
	glAttachShader(shader_program, vertex.getShader());
	glLinkProgram(shader_program);
	//Check for linker errors
	int params = -1;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
	{
		glLog::gl_log_err("ERROR: GL shader index %i did not link\n", shader_program);
		glLog::print_program_info_log(shader_program);
	}

}

void Program::use()
{
	glUseProgram(shader_program);
}

int Program::getUniform(const char* name)
{
	int location = glGetUniformLocation(shader_program, name);
	if (location == -1)
		glLog::gl_log_err("ERROR: Uniform %s was not found\n", name);
	else
		return location;
}