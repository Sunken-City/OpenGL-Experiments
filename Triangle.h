#pragma once

#include "Geometry.h"
#include "Vec3.h"

class Triangle : public virtual Geometry
{
public:
	Triangle(glm::vec3 first, glm::vec3 second, glm::vec3 third);
	~Triangle();
	void draw();

private:
	GLuint points_vbo = 0;
	GLuint colors_vbo = 0;
	GLuint vao = 0;
};