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
		prim_verts.push_back(verts.at(i).x);
		prim_verts.push_back(verts.at(i).y);
		prim_verts.push_back(verts.at(i).z);
		glLog::gl_log_err("X: %f Y: %f Z: %f\n", verts.at(i).x, verts.at(i).y, verts.at(i).z);
	}

	//Set up the cube faces.
	indices.push_back(Index(0, 1, 2));
	indices.push_back(Index(0, 2, 6));
	indices.push_back(Index(0, 4, 6));
	indices.push_back(Index(1, 2, 3));
	indices.push_back(Index(1, 7, 3));
	indices.push_back(Index(1, 5, 7));

	indices.push_back(Index(4, 5, 1));
	indices.push_back(Index(4, 1, 0));
	indices.push_back(Index(6, 2, 3));
	indices.push_back(Index(6, 7, 3));
	indices.push_back(Index(6, 5, 7));
	indices.push_back(Index(6, 4, 7));
	for (int i = 0; i < 12; i++)
	{
		prim_indices.push_back(indices.at(i).first);
		prim_indices.push_back(indices.at(i).second);
		prim_indices.push_back(indices.at(i).third);
	}
	Geometry::init();
}

Cube::~Cube()
{

}

void Cube::draw()
{
	Geometry::draw();
}