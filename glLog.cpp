#include "glLog.h"

//Disable fopen deprecation warning
#pragma warning(push)
#pragma warning(disable: 4996)

bool glLog::restart_gl_log()
{
	FILE* file = fopen(GL_LOG_FILE, "w");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open log file %s for writing\n", GL_LOG_FILE);
		return false;
	}
	time_t now = time(NULL);
	char* date = ctime(&now);
	fprintf(file, "GL_LOG_FILE log. Local time %s\n", date);
	fclose(file);
	return true;
}

//Log out a message to our log file.
bool glLog::gl_log(const char* message, ...)
{
	va_list argptr;
	FILE* file = fopen(GL_LOG_FILE, "a");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open log file %s for appending\n", GL_LOG_FILE);
		return false;
	}

	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	//Close the file so that we ensure our file loses no info
	fclose(file);
	return true;
}

//Log out a message to our log file and to stderr simultaneously.
bool glLog::gl_log_err(const char* message, ...)
{
	va_list argptr;
	FILE* file = fopen(GL_LOG_FILE, "a");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open log file %s for appending\n", GL_LOG_FILE);
		return false;
	}

	//Print to file first
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);

	//Now print to stderr
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);

	//Close the file so that we ensure our file loses no info
	fclose(file);
	return true;
}

//A wrapper for our error logging
void glLog::glfw_error_callback(int error, const char* description)
{
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

void glLog::print_shader_info_log(GLuint shader_index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
	gl_log_err("Shader info log for GL index %u: \n%s\n", shader_index, log);
}

void glLog::print_program_info_log(GLuint program)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog(program, max_length, &actual_length, log);
	gl_log_err("Program info log for GL index %u: \n%s\n", program, log);
}

void glLog::print_all(GLuint program) 
{
	gl_log_err("--------------------\nshader program %i info:\n", program);
	int params = -1;
	glGetProgramiv(program, GL_LINK_STATUS, &params);
	gl_log_err("GL_LINK_STATUS = %i\n", params);

	glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
	gl_log_err("GL_ATTACHED_SHADERS = %i\n", params);

	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
	gl_log_err("GL_ACTIVE_ATTRIBUTES = %i\n", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib(program, i, max_length, &actual_length, &size, &type, name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(program, long_name);
				gl_log_err("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
			}
		}
		else {
			int location = glGetAttribLocation(program, name);
			gl_log_err("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
		}
	}

	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
	gl_log_err("GL_ACTIVE_UNIFORMS = %i\n", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform(program, i, max_length, &actual_length, &size, &type, name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetUniformLocation(program, long_name);
				gl_log_err("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
			}
		}
		else {
			int location = glGetUniformLocation(program, name);
			gl_log_err("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
		}
	}

	glLog::print_program_info_log(program);
}

const char* glLog::GL_type_to_string(GLenum type) 
{
	switch (type) {
	case GL_BOOL: return "bool";
	case GL_INT: return "int";
	case GL_FLOAT: return "float";
	case GL_FLOAT_VEC2: return "vec2";
	case GL_FLOAT_VEC3: return "vec3";
	case GL_FLOAT_VEC4: return "vec4";
	case GL_FLOAT_MAT2: return "mat2";
	case GL_FLOAT_MAT3: return "mat3";
	case GL_FLOAT_MAT4: return "mat4";
	case GL_SAMPLER_2D: return "sampler2D";
	case GL_SAMPLER_3D: return "sampler3D";
	case GL_SAMPLER_CUBE: return "samplerCube";
	case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
	default: break;
	}
	return "other";
}

#pragma warning(pop)