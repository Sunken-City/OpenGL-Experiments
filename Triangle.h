#pragma once

#include <vector>
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
#include <glm/glm.hpp>

class Triangle
{
public:
	Triangle(glm::vec3 first, glm::vec3 second, glm::vec3 third);
	~Triangle();

	glm::vec3 norm;

private:
};