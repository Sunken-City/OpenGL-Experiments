#include "Triangle.h"


Triangle::Triangle(glm::vec3 first, glm::vec3 second, glm::vec3 third)
{
	GLfloat points[] = { first.x,  first.y,  first.z,
						second.x, second.y, second.z,
						 third.x,  third.y,  third.z };
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	//Generate an empty buffer for the points
	glGenBuffers(1, &points_vbo);
	//Set the above as our current buffer via "binding"
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//Copy points into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//Generate an empty buffer for the colors
	glGenBuffers(1, &colors_vbo);
	//Set the above as our current buffer via "binding"
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	//Copy points into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//Set up the vertex attribute object (VAO)
	//We make an int to associate our VAO with.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Enable the first attribute, 0, which is our Points buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//0 means to define the layout for attrib #0, 3 means that we're using vec3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Enable the first attribute, 1, which is our Colors buffer
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	//0 means to define the layout for attrib #0, 3 means that we're using vec3
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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