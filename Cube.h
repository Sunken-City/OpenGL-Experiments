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
};