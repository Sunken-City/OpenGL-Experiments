#include "Triangle.h"


Triangle::Triangle(glm::vec3 first, glm::vec3 second, glm::vec3 third)
{
	GLfloat points[] = { first.x,  first.y,  first.z,
						second.x, second.y, second.z,
						 third.x,  third.y,  third.z };
	//Generate an empty buffer
	glGenBuffers(1, &vbo);
	//Set the above as our current buffer via "binding"
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Copy points into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) * 9, points, GL_STATIC_DRAW);

	//Set up the vertex attribute object (VAO)
	//We make an int to associate our VAO with.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//Enable the first attribute, 0. We know this because we're using only one vao
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//0 means to define the layout for attrib #0, 3 means that we're using vec3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

Triangle::~Triangle()
{

}

void Triangle::draw()
{
	glBindVertexArray(vao);
	//Draw the three points from our VAO with our current shader
	glDrawArrays(GL_TRIANGLES, 0, 3);
}