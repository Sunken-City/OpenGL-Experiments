#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
// Include GLM core features
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(int MVPLocation);
	~Camera();

	void updateMVP();
	void move(GLFWwindow* window, double elapsedSeconds);

private:
	float speed = 1.0f; //1 unit per second
	float yawSpeed = 5.0f; //5 degrees per second
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 10.0f);
	float yaw = 0.0f; //Y rotation in degrees.
	int MVPLocation;

};