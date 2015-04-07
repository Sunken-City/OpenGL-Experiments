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
		faces.push_back(new Face(verts.at(indices.at(i).first), verts.at(indices.at(i).second), verts.at(indices.at(i).third)));
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
				glLog::gl_log_err("Vert %i is part of Face {%i, %i, %i}\n", i, indices.at(j).first, indices.at(j).second, indices.at(j).third);
				//Add the face's normal to our collection of normals
				glLog::gl_log_err("Face {%i, %i, %i} has Normal {%f, %f, %f}\n", indices.at(j).first, indices.at(j).second, indices.at(j).third, faces.at(j)->norm.x, faces.at(j)->norm.y, faces.at(j)->norm.z);
				
				normals += faces.at(j)->norm;
			}
		}

		glLog::gl_log_err("Normal before Normalizing {%f, %f, %f}\n", normals.x, normals.y, normals.z);

		//Create our vetex normal
		glm::vec3 normalizedNormals;
		if (normals != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			normalizedNormals = glm::normalize(normals);
		}
		else
			normalizedNormals = normals;
		
		//Store our vertex normal.
		norms.push_back(normalizedNormals.x);
		norms.push_back(normalizedNormals.y);
		norms.push_back(normalizedNormals.z);
		glLog::gl_log_err("Vert {%f, %f, %f} has Normal {%f, %f, %f}\n", verts.at(i).x, verts.at(i).y, verts.at(i).z, normalizedNormals.x, normalizedNormals.y, normalizedNormals.z);
	}
}