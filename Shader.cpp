#include "Shader.h"

Shader::Shader()
{

}

Shader::Shader(const char* fileName, GLuint shaderType)
{
	//Read the entire file into a char* first
	std::ifstream shaderFile(fileName);
	std::string fileText = "";
	while (shaderFile.good()) {
		std::string line;
		std::getline(shaderFile, line);
		fileText.append(line + "\n");
	}
	const char* program = fileText.c_str();

	//Now we need to load the shader files into a GL shader
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &program, NULL);
	glCompileShader(shader);
	//Check for compile errors
	int params = -1;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		glLog::gl_log_err("ERROR: GL shader index %i did not compile\n", shader);
		glLog::print_shader_info_log(shader);
		glLog::gl_log_err("Shader file dump: \n%s", program);
	}
}

GLuint Shader::getShader()
{
	return shader;
}