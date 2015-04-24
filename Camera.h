#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
// Include GLM core features
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Program.h"

class Camera
{
public:
	Camera(Program shader);
	~Camera();

	void updateMVP();
	void move(GLFWwindow* window, double elapsedSeconds);
	int getMVPLocation();
	int getModelLocation();
	int getViewLocation();
	int getNormalLocation();

private:
	float speed = 1.0f; //1 unit per second
	float rotationSpeed = 2.5f; //2.5 degrees per second
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
	float pitch = 0.0f; //X rotation in degrees.
	float yaw = 0.0f; //Y rotation in degrees.
	float roll = 0.0f; //Z rotation in degrees.
	int MVPLocation;
	int ModelLocation;
	int ViewLocation;
	int NormalLocation;

};