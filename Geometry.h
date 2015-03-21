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
	virtual void init();
	virtual void draw();

	std::vector<glm::vec3> verts; //Vertecies of the object.
	std::vector<GLfloat> prim_verts; //Vertecies of the object.
	std::vector<Index> indices; //The index numbers that make up the faces of the object.
	std::vector<GLuint> prim_indices;
	GLuint vao = 0;
	GLuint points_vbo = 0;
	GLuint colors_vbo = 0;
	GLuint index_vbo = 0;
};