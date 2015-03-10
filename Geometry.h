#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.

class Geometry
{
public:
	Geometry();
	~Geometry();
	virtual void draw();
};