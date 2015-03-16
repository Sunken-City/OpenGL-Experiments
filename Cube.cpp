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

	//Create triangles based on the indices we use.
	for (int i = 0; i < 12; i++)
	{
		faces.push_back(Triangle(verts.at(indices.at(i).first), verts.at(indices.at(i).second), verts.at(indices.at(i).third)));
	}
}

Cube::~Cube()
{

}

void Cube::draw()
{
	for (int i = 0; i < 12; i++)
	{
		faces.at(i).draw();
	}
}