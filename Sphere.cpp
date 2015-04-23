#include "Sphere.h"
#include "glLog.h"
#include "math.h"

Sphere::Sphere(GLfloat size, int iterations)
{
	//Generate points to use for the sphere algorithm
	glm::vec3 p1 = { 0, 0, size };
	glm::vec3 p2 = { 0, 0, -size };
	glm::vec3 p3 = { -size, -size, 0 };
	glm::vec3 p4 = { size, -size, 0 };
	glm::vec3 p5 = { size, size, 0 };
	glm::vec3 p6 = { -size,  size, 0 };

	p1 = glm::normalize(p1);
	p2 = glm::normalize(p2);
	p3 = glm::normalize(p3);
	p4 = glm::normalize(p4);
	p5 = glm::normalize(p5);
	p6 = glm::normalize(p6);

	verts.push_back(p1);
	verts.push_back(p2);
	verts.push_back(p3);
	verts.push_back(p4);
	verts.push_back(p5);
	verts.push_back(p6);

	indices.push_back(Index(0, 3, 4));
	indices.push_back(Index(0, 4, 5));
	indices.push_back(Index(0, 5, 2));
	indices.push_back(Index(0, 2, 3)); 
	indices.push_back(Index(1, 4, 3));
	indices.push_back(Index(1, 5, 4));
	indices.push_back(Index(1, 2, 5));
	indices.push_back(Index(1, 3, 2));

	/*
	std::vector <Face> faces;
	faces.push_back(Face(p1, p2, p3));
	faces.push_back(Face(p2, p1, p4));
	faces.push_back(Face(p2, p4, p3));
	faces.push_back(Face(p1, p3, p4));
	faces.resize(pow(4, iterations));
	int n = 4;
	for (int i = 1; i<iterations; i++) {
		int nstart = n;

		for (int j = 0; j<nstart; j++) {

			// Create initially copies for the new facets 
			faces.at(n) = faces.at(j);
			faces.at(n + 1) = faces.at(j);
			faces.at(n + 1) = faces.at(j);

			// Calculate the midpoints 
			p1 = MidPoint(facets[j].p1, facets[j].p2);
			p2 = MidPoint(facets[j].p2, facets[j].p3);
			p3 = MidPoint(facets[j].p3, facets[j].p1);

			// Replace the current facet 
			facets[j].p2 = p1;
			facets[j].p3 = p3;

			// Create the changed vertices in the new facets 
			facets[n].p1 = p1;
			facets[n].p3 = p2;
			facets[n + 1].p1 = p3;
			facets[n + 1].p2 = p2;
			facets[n + 2].p1 = p1;
			facets[n + 2].p2 = p2;
			facets[n + 2].p3 = p3;
			n += 3;
		}
	}

	for (j = 0; j<n; j++) {
		Normalise(&facets[j].p1);
		Normalise(&facets[j].p2);
		Normalise(&facets[j].p3);
	} */

	/*
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

	for (int i = 0; i < 12; i++)
	{
		prim_indices.push_back(indices.at(i).first);
		prim_indices.push_back(indices.at(i).second);
		prim_indices.push_back(indices.at(i).third);
	}*/
	Geometry::init();
}

Sphere::~Sphere()
{

}

glm::vec3 midpoint(glm::vec3 first, glm::vec3 second)
{
	glm::vec3 p;
	p.x = (first.x + second.x) / 2;
	p.y = (first.y + second.y) / 2;
	p.z = (first.z + second.z) / 2;
	return(p);
}

void Sphere::draw()
{
	Geometry::draw();
}