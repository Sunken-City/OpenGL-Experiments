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

#pragma warning(pop)