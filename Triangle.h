#pragma once

#include "Geometry.h"

class Triangle : public virtual Geometry
{
public:
	Triangle(GLuint shader_program);
	~Triangle();
	void init();
	void draw();

private:
	GLuint shaderProgram;
};