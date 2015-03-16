#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
#include <glm/vec3.hpp>
#include <vector>

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
	//virtual void init() = 0;
	virtual void draw();

	std::vector<glm::vec3> verts; //Vertecies of the object.
	std::vector<Index> indices; //The index numbers that make up the faces of the object.
	GLuint vao = 0;
	//std::vector<Triangle> faces; //The triangles that make up the faces of the cube.
};