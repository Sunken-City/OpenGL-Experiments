#pragma once
#include <vector>

#include "Geometry.h"
#include "Face.h"

class Sphere : public virtual Geometry	
{
public:
	Sphere(GLfloat size, int iterations);
	~Sphere();
	glm::vec3 midpoint(glm::vec3 first, glm::vec3 second);
	void draw();
};