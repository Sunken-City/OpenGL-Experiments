#include "Triangle.h"

Triangle::Triangle()
{
	//This class is made to test out the shader and the normals, so I haven't added a useful constructor yet.
	verts.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	verts.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	verts.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	//Temporarily making this a square :P
	verts.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));

	indices.push_back(Index(1, 0, 2));
	indices.push_back(Index(1, 2, 3));

	Geometry::init();
}

Triangle::~Triangle()
{

}

void Triangle::draw()
{
	Geometry::draw();
}