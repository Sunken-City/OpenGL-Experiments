#pragma once
#include <vector>

#include "Geometry.h"
#include "Triangle.h"

class Cube : public virtual Geometry	
{
public:
	Cube(glm::vec3 verts[8]);
	~Cube();
	void draw();

private:
	std::vector<glm::vec3> verts; //Vertecies of the cube.
	std::vector<Triangle> faces; //The triangles that make up the faces of the cube.
	std::vector<Index> indices; //The index numbers that make up the faces of the cube.
};