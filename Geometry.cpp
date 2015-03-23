#include "Geometry.h"


Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

void Geometry::init()
{
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	createFaces();
	createNormals();

	//Set up the vertex attribute object (VAO)
	//We make an int to associate our VAO with.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Generate an empty buffer for the points
	glGenBuffers(1, &points_vbo);
	//Set the above as our current buffer via "binding"
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//Copy points into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(prim_verts.at(0)) * static_cast<int>(prim_verts.size()), prim_verts.data(), GL_STATIC_DRAW);

	//Generate an empty buffer for the colors
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//Generate an empty buffer for the colors
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(norms.at(0)) * static_cast<int>(norms.size()), norms.data(), GL_STATIC_DRAW);

	//Generate the indices and send them to the graphics card
	glGenBuffers(1, &index_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int>(prim_indices.size()) * sizeof(prim_indices.at(0)), prim_indices.data(), GL_STATIC_DRAW);

	//Enable the first attribute, 0, which is our Points buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//0 means to define the layout for attrib #0, 3 means that we're using vec3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Enable the Colors attribute, 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Enable the Normals attribute, 2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Geometry::draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void Geometry::createFaces()
{
	for (int i = 0; i < indices.size(); i++)
	{
		faces.push_back(new Triangle(verts.at(indices.at(i).first), verts.at(indices.at(i).second), verts.at(indices.at(i).third)));
	}
}

void Geometry::createNormals()
{
	//Get a normal for each vertex
	for (int i = 0; i < verts.size(); i++)
	{
		GLfloat vertexNormal = 0.0f;
		glm::vec3 normals;
		//std::vector<Triangle*> connectedFaces;

		//Find the connected faces
		for (int j = 0; j < indices.size(); j++)
		{
			if (indices.at(j).first == i || indices.at(j).second == i || indices.at(j).third == i)
			{
				//Add the face's normal to our collection of normals
				normals += faces.at(j)->norm;
			}
		}

		//Create our vetex normal
		glm::vec3 normalizedNormals = glm::normalize(normals);
		
		//Store our vertex normal.
		norms.push_back(normalizedNormals.x);
		norms.push_back(normalizedNormals.y);
		norms.push_back(normalizedNormals.z);
	}
}