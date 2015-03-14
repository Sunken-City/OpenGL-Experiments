#include "Cube.h"

Cube::Cube(glm::vec3 vertices[8])
{
	//Add all of the vertices to the vector of verts.
	for (int i = 0; i < 8; i++)
	{
		verts.push_back(vertices[i]);
	}

	//Set up the cube faces.
	indices.push_back(Index(0, 1, 2));
	indices.push_back(Index(0, 3, 4));
	indices.push_back(Index(0, 5, 6));
	indices.push_back(Index(1, 6, 7));
	indices.push_back(Index(7, 4, 3));
	indices.push_back(Index(4, 7, 6));

	indices.push_back(Index(2, 3, 0));
	indices.push_back(Index(4, 5, 0));
	indices.push_back(Index(6, 1, 0));
	indices.push_back(Index(7, 2, 1));
	indices.push_back(Index(3, 2, 7));
	indices.push_back(Index(6, 5, 4));

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