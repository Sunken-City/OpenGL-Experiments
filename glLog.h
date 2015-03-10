#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#define GL_LOG_FILE "gl.log"

class glLog
{
public:
	static bool restart_gl_log();
	//Log out a message to our log file.
	static bool gl_log(const char* message, ...);
	//Log out a message to our log file and to stderr simultaneously.
	static bool gl_log_err(const char* message, ...);
	//A wrapper for our error logging
	static void glfw_error_callback(int error, const char* description);
	//Print the shader info log for compilation
	static void print_shader_info_log(GLuint shader_index);
	//Print the program info log for linking
	static void print_program_info_log(GLuint program);
	//Anton's function to print out all of the shader info
	static void print_all(GLuint program);
	//Anton's helper function to get strings out of GL Enum types
	static const char* GL_type_to_string(GLenum type);
};