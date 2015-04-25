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

	for (int i = 0; i < iterations; i++)
	{
		int n = indices.size();
		for (int j = 0; j < n; j++)
		{
			// Calculate the midpoints 
			glm::vec3 point1 = midpoint(verts.at(indices.at(j).first), verts.at(indices.at(j).second));
			glm::vec3 point2 = midpoint(verts.at(indices.at(j).second), verts.at(indices.at(j).third));
			glm::vec3 point3 = midpoint(verts.at(indices.at(j).third), verts.at(indices.at(j).first));

			//Move the points to the outside of our sphere.
			point1 = glm::normalize(point1);
			point2 = glm::normalize(point2);
			point3 = glm::normalize(point3);

			//Add these vertices to the list of verts, and store their array location.
			//Naiive way to check for dupes is here. I'll find a better solution later.
			int point1Location = -1;
			int point2Location = -1;
			int point3Location = -1;
			for (int z = 0; z < verts.size(); z++)
			{
				glm::vec3 compare = verts.at(z);
				if (compare == point1)
					point1Location = z;
				if (compare == point2)
					point2Location = z;
				if (compare == point3)
					point3Location = z;
			}
			if (point1Location == -1)
			{
				point1Location = verts.size();
				verts.push_back(point1);
			}

			if (point2Location == -1)
			{
				point2Location = verts.size();
				verts.push_back(point2);
			}

			if (point3Location == -1)
			{
				point3Location = verts.size();
				verts.push_back(point3);
			}

			//Create 3 new faces (the outer triangles, the pieces of the triforce)
			indices.push_back(Index(indices.at(j).first, point1Location, point3Location));
			indices.push_back(Index(point1Location, indices.at(j).second, point2Location));
			indices.push_back(Index(point3Location, point2Location, indices.at(j).third));

			//Replace the original face with the inner, upside-down triangle (not the triforce)
			indices.at(j).first = point1Location;
			indices.at(j).second = point2Location;
			indices.at(j).third = point3Location;
		}
	}
	Geometry::init();
}

Sphere::~Sphere()
{

}

//Finds the midpoint of two vectors.
glm::vec3 Sphere::midpoint(glm::vec3 first, glm::vec3 second)
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