#include "Cube.h"
#include "glLog.h"

Cube::Cube(GLfloat size)
{
	GLfloat adjustedSize = size / 2.0f;
	//Add all of the vertices to the vector of verts.
	for (int i = 0; i < 8; i++)
	{
		verts.push_back(glm::vec3(((i & 0x01) == 0) ? adjustedSize : -adjustedSize, 
								  ((i & 0x02) == 0) ? adjustedSize : -adjustedSize, 
								  ((i & 0x04) == 0) ? adjustedSize : -adjustedSize));
	}

	//Set up the cube faces.
	indices.push_back(Index(0, 2, 1));
	indices.push_back(Index(1, 2, 3));

	indices.push_back(Index(0, 6, 2));
	indices.push_back(Index(0, 4, 6));

	indices.push_back(Index(4, 5, 0));
	indices.push_back(Index(5, 1, 0));

	indices.push_back(Index(4, 5, 6));
	indices.push_back(Index(5, 7, 6));

	indices.push_back(Index(5, 3, 7));
	indices.push_back(Index(1, 3, 5));

	indices.push_back(Index(6, 2, 7));
	indices.push_back(Index(7, 2, 3));
	Geometry::init();
}

Cube::~Cube()
{

}

void Cube::draw()
{
	Geometry::draw();
}