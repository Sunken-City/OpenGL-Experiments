#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.

// Include GLM core features
#include <glm/vec3.hpp>

#include <stdio.h>
#include <assert.h>

#include "glLog.h"
#include "Shader.h"
#include "Program.h"
#include "Cube.h"

using namespace glm;

int main()
{
	assert(glLog::restart_gl_log());
	glLog::gl_log("starting GLFW\n%s\n", glfwGetVersionString());
	
	//Use our function for the call-back function for GLFW
	glfwSetErrorCallback(glLog::glfw_error_callback);

	//Start GL context and window using GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: Couldn't start GLFW3\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "ERROR: Couldn't create a window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	//Start GLEW extension handler
	glewExperimental = GL_TRUE; //Improves support for newer OpenGL releases
	glewInit();

	//Get version info
	const GLubyte* renderer = glGetString(GL_RENDER); //Get the renderer string
	const GLubyte* version = glGetString(GL_VERSION); //Get the version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	//Tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); //Enable depth testing
	glDepthFunc(GL_LESS); //Depth testing interprets a smaller value as "closer"

	vec3 vertices[] = {
		vec3(0.5f, 0.5f, 0.5f),
		vec3(-0.5f, 0.5f, 0.5f),
		vec3(0.5f, -0.5f, 0.5f),
		vec3(-0.5f, -0.5f, 0.5f),
		vec3(0.5f, 0.5f, -0.5f),
		vec3(-0.5f, 0.5f, -0.5f),
		vec3(0.5f, -0.5f, -0.5f),
		vec3(-0.5f, -0.5f, -0.5f)
	};

	Cube cube = Cube(vertices);
	
	Shader vs = Shader("vertex_shader.vert", GL_VERTEX_SHADER);
	Shader fs = Shader("fragment_shader.frag", GL_FRAGMENT_SHADER);

	Program shaderProgram = Program(vs, fs);

	while (!glfwWindowShouldClose(window))
	{
		//Clear the drawing screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
		
		shaderProgram.use();
		cube.draw();
		//Update other events, such as input handling
		glfwPollEvents();
		//Display what we've drawn
		glfwSwapBuffers(window);
	}
	//Close our GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}