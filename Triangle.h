#pragma once

#include "Geometry.h"
#include "Vec3.h"

class Triangle : public virtual Geometry
{
public:
	Triangle(GLfloat points[9]);
	~Triangle();
	void init();
	void draw();

private:
	GLuint vbo = 0;
	GLuint vao = 0;
	GLfloat* pointsPointer;
};