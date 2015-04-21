#include "Face.h"


Face::Face(glm::vec3 first, glm::vec3 second, glm::vec3 third)
{
	GLfloat points[] = { first.x,  first.y,  first.z,
						second.x, second.y, second.z,
						 third.x,  third.y,  third.z };
	//Calculate the normal for this face
	glm::vec3 v0 = second - first;
	glm::vec3 v1 = third - first;

	//norm.x = (v0.y * v1.z) - (v0.z * v1.y);
	//norm.y = (v0.z * v1.x) - (v0.x * v1.z);
	//norm.z = (v0.x * v1.y) - (v0.y * v1.x);
	norm = glm::normalize(glm::cross(v1, v0));
}

Face::~Face()
{

}