#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.

// Include GLM core features
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <stdio.h>
#include <assert.h>

#include "glLog.h"
#include "Shader.h"
#include "Program.h"
#include "Cube.h"

using namespace glm;

void updateMVP(glm::vec3 camPos, float camYaw, int MVPLocation)
{
	glm::mat4 Translation = glm::translate(glm::mat4(), -camPos);
	glm::mat4 Rotation = glm::rotate(glm::mat4(), -camYaw, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 View = Rotation * Translation;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &MVP[0][0]);
}

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

	Cube cube = Cube(3);
	
	Shader vs = Shader("vertex_shader.vert", GL_VERTEX_SHADER);
	Shader fs = Shader("fragment_shader.frag", GL_FRAGMENT_SHADER);

	Program shaderProgram = Program(vs, fs);

	//Camera stuff.
	float cam_speed = 1.0f; //1 unit per second
	float cam_yaw_speed = 5.0f; //5 degrees per second
	glm::vec3 camPos = vec3(0.0f, 0.0f, 10.0f);
	float camYaw = 0.0f; //Y rotation in degrees.

	int MVPLocation = shaderProgram.getUniform("MVP");
	shaderProgram.use();

	updateMVP(camPos, camYaw, MVPLocation);


	while (!glfwWindowShouldClose(window))
	{
		//Update our Timer
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;

		//Camera Control
		bool camMoved = false;
		
		//If holding left shift, "Run"
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		{
			cam_speed = 2.0f;
			cam_yaw_speed = 10.0f;
		}
		else
		{
			cam_speed = 1.0f;
			cam_yaw_speed = 5.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			camPos.x -= cam_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			camPos.x += cam_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE))
		{
			camPos.y += cam_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
		{
			camPos.y -= cam_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			camPos.z -= cam_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			camPos.z += cam_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			camYaw += cam_yaw_speed * elapsedSeconds;
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_E))
		{
			camYaw -= cam_yaw_speed * elapsedSeconds;
			camMoved = true;
		}
		if (camMoved)
		{
			updateMVP(camPos, camYaw, MVPLocation);
		}





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