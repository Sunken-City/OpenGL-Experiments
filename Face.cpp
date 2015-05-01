#include "Face.h"

Face::Face(glm::vec3 first, glm::vec3 second, glm::vec3 third)
{
	GLfloat points[] = { first.x,  first.y,  first.z,
						second.x, second.y, second.z,
						 third.x,  third.y,  third.z };
	//Calculate the normal for this face
	glm::vec3 v0 = second - first;
	glm::vec3 v1 = third - first;
	norm = glm::normalize(glm::cross(v0, v1));
}

Face::~Face()
{

}