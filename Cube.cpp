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