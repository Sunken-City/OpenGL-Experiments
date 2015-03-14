#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
#include <glm/vec3.hpp>

class Index
{
public:
	Index(int first, int second, int third) :first(first), second(second), third(third){}
	int first;
	int second;
	int third;
};

class Geometry
{
public:
	Geometry();
	~Geometry();
	virtual void draw();
};