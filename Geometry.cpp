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

	initPrims();

	createFaces();
	createNormals();
	initInterleaved();

	//Set up the vertex attribute object (VAO)
	//We make an int to associate our VAO with.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Generate an empty buffer for the points
	glGenBuffers(1, &points_vbo);
	//Set the above as our current buffer via "binding"
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//Copy points into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(interleaved.at(0)) * static_cast<int>(interleaved.size()), interleaved.data(), GL_STATIC_DRAW);

	//Generate an empty buffer for the colors
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	/*

	//Generate an empty buffer for the points
	glGenBuffers(1, &points_vbo);
	//Set the above as our current buffer via "binding"
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//Copy points into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(prim_verts.at(0)) * static_cast<int>(prim_verts.size()), prim_verts.data(), GL_STATIC_DRAW);


	//Generate an empty buffer for the colors
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(norms.at(0)) * static_cast<int>(norms.size()), norms.data(), GL_STATIC_DRAW);
	*/
	//Generate the indices and send them to the graphics card
	glGenBuffers(1, &index_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(prim_indices.at(0)) * static_cast<int>(prim_indices.size()), prim_indices.data(), GL_STATIC_DRAW);

	//Enable the first attribute, 0, which is our Points buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	//0 means to define the layout for attrib #0, 3 means that we're using vec3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(0));
	//Enable Normals attribute, 2
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(12));

	//Enable the Colors attribute, 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);



	/*
	//Enable the Normals attribute, 2
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	*/
}

void Geometry::draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void Geometry::createFaces()
{
	for (int i = 0; i < indices.size(); i++)
	{
		faces.push_back(new Face(verts.at(indices.at(i).first), verts.at(indices.at(i).second), verts.at(indices.at(i).third)));
	}
}

void Geometry::createNormals()
{
	int normalCount = 0;
	//Get a normal for each vertex
	for (int i = 0; i < verts.size(); i++)
	{
		GLfloat vertexNormal = 0.0f;
		glm::vec3 normals;
		
		//Find the connected faces
		for (int j = 0; j < indices.size(); j++)
		{
			if (indices.at(j).first == i || indices.at(j).second == i || indices.at(j).third == i)
			{
				//Add the face's normal to our collection of normals
				normals += faces.at(j)->norm;
				normalCount++;
			}
		}
		//Create our vetex normal
		glm::vec3 normalizedNormals = normals;
		if (normals != glm::vec3(0.0f, 0.0f, 0.0f))
			normalizedNormals = glm::normalize(normals);

		//Store our vertex normal.
		norms.push_back(normalizedNormals.x);
		norms.push_back(normalizedNormals.y);
		norms.push_back(normalizedNormals.z);
	}
}

void Geometry::initPrims()
{
	for (int i = 0; i < verts.size(); i++)
	{
		prim_verts.push_back(verts.at(i).x);
		prim_verts.push_back(verts.at(i).y);
		prim_verts.push_back(verts.at(i).z);
	}
	for (int i = 0; i < indices.size(); i++)
	{
		prim_indices.push_back(indices.at(i).first);
		prim_indices.push_back(indices.at(i).second);
		prim_indices.push_back(indices.at(i).third);
	}

}

void Geometry::initInterleaved()
{
	for (int i = 0; i < prim_verts.size(); i++)
	{
		int counter = i;
		interleaved.push_back(prim_verts.at(counter++)); //x
		interleaved.push_back(prim_verts.at(counter++)); //y
		interleaved.push_back(prim_verts.at(counter)); //z
		interleaved.push_back(norms.at(i++));
		interleaved.push_back(norms.at(i++));
		interleaved.push_back(norms.at(i));
	}
}