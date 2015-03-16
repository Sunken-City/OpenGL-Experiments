#pragma once
#include <vector>

#include "Geometry.h"
#include "Triangle.h"

class Cube : public virtual Geometry	
{
public:
	Cube(GLfloat size);
	~Cube();
	void draw();

private:

	std::vector<Triangle> faces; //The triangles that make up the faces of the cube.
};