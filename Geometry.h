#pragma once
#include <GL/glew.h> // Include GLEW, which helps us map to drivers
#include <GLFW/glfw3.h> // Include GLFW, the Windowing Tool Kit we're using.
#include <glm/vec3.hpp>
#include <vector>

#include "Face.h"
#include "glLog.h"

//Ira Greenburg's workaround for getting the interleaved buffer
#define BUFFER_OFFSET(i) ((void*)(i))

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

	//3 Pos + 3 Norm
	enum {STRIDE = 6};

	std::vector<glm::vec3> verts; //Vertecies of the object.
	std::vector<GLfloat> prim_verts; //Vertecies of the object as primatives.
	std::vector<Index> indices; //The index numbers that make up the faces of the object.
	std::vector<GLuint> prim_indices; //The index numbers that make up the faces of the object as primatives.
	std::vector<Face*> faces;
	std::vector<GLfloat> norms; //Normals of the object as primatives.
	std::vector<GLfloat> interleaved;
	GLuint vao = 0;
	GLuint points_vbo = 0;
	GLuint colors_vbo = 0;
	GLuint index_vbo = 0;
	GLuint normals_vbo = 0;

private:
	void initPrims();
	void createFaces();
	void createNormals();
	void initInterleaved();
};