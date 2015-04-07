#include "Triangle.h"

Triangle::Triangle()
{
	//This class is made to test out the shader and the normals, so I haven't added a useful constructor yet.
	verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	prim_verts.push_back(1.0f);
	prim_verts.push_back(1.0f);
	prim_verts.push_back(1.0f);

	verts.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	prim_verts.push_back(-1.0f);
	prim_verts.push_back(1.0f);
	prim_verts.push_back(0.0f);

	verts.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	prim_verts.push_back(1.0f);
	prim_verts.push_back(-1.0f);
	prim_verts.push_back(1.0f);
	
	//Temporarily making this a square :P

	verts.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	prim_verts.push_back(-1.0f);
	prim_verts.push_back(-1.0f);
	prim_verts.push_back(0.0f);

	indices.push_back(Index(0, 1, 2));
	prim_indices.push_back(indices.at(0).first);
	prim_indices.push_back(indices.at(0).second);
	prim_indices.push_back(indices.at(0).third);

	indices.push_back(Index(1, 2, 3));
	prim_indices.push_back(indices.at(1).first);
	prim_indices.push_back(indices.at(1).second);
	prim_indices.push_back(indices.at(1).third);

	Geometry::init();
}

Triangle::~Triangle()
{

}

void Triangle::draw()
{
	Geometry::draw();
}