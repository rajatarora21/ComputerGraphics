#include "sphere.h"
#include <iostream>
#include <list>
#include <vector>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

using namespace std;
using namespace glm;

sphere::sphere() {}
sphere::~sphere()
{
}
;

int sphere::createSphereArray()
{
	// sphere model
	vector<glm::vec3> vertexArray;
	vector<glm::vec3> tempVertex;

	float segment = 36;
	float slice = 72;
	for (size_t j = 0; j < slice+1; j++)
	{
		for (int i = 0; i < segment+1; i++)
		{
			float theta = pi<float>()*(j /slice - 0.5);
			float psi = 2*pi<float>()*(i /segment);
			//pos
			tempVertex.push_back({ cos(theta)*sin(psi) ,sin(theta),cos(theta)*cos(psi) });
			//uv
			tempVertex.push_back({ i/(segment-1),j/(slice-1),0});
			//normal
			tempVertex.push_back({ cos(theta)*sin(psi) ,sin(theta),cos(theta)*cos(psi) });
		}
	}

	for (size_t j = 0; j < slice; j++)
	{
		for (int i = 0; i < segment; i++)
		{
			int t0 = (i) % int(segment + 1) + (j)*int(segment + 1);
			int t1 = (i + 1) % int(segment + 1) + (j)*int(segment + 1);
			int t2 = (i + 1) % int(segment + 1) + (j+1)*int(segment + 1);
			int t3 = (i) % int(segment + 1) + (j)*int(segment + 1);
			int t4 = (i + 1) % int(segment + 1) + (j + 1)*int(segment + 1);
			int t5 = (i) % int(segment + 1) + (j + 1)*int(segment + 1);
			vertexArray.push_back(tempVertex[3 * t0]);
			vertexArray.push_back(tempVertex[3 * t0 + 1]);
			vertexArray.push_back(tempVertex[3 * t0 + 2]);
			vertexArray.push_back(tempVertex[3 * t1]);
			vertexArray.push_back(tempVertex[3 * t1 + 1]);
			vertexArray.push_back(tempVertex[3 * t1 + 2]);
			vertexArray.push_back(tempVertex[3 * t2]);
			vertexArray.push_back(tempVertex[3 * t2 + 1]);
			vertexArray.push_back(tempVertex[3 * t2 + 2]);
			vertexArray.push_back(tempVertex[3 * t3]);
			vertexArray.push_back(tempVertex[3 * t3 + 1]);
			vertexArray.push_back(tempVertex[3 * t3 + 2]);
			vertexArray.push_back(tempVertex[3 * t4]);
			vertexArray.push_back(tempVertex[3 * t4 + 1]);
			vertexArray.push_back(tempVertex[3 * t4 + 2]);
			vertexArray.push_back(tempVertex[3 * t5]);
			vertexArray.push_back(tempVertex[3 * t5 + 1]);
			vertexArray.push_back(tempVertex[3 * t5 + 2]);
		}
	}

	size = vertexArray.size() / 3;
	// Create a vertex array
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray[0])*vertexArray.size(), vertexArray.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(vec3),
		(void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(vec3),
		(void*)(sizeof(vec3)*2)     // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindVertexArray(0);

	return vertexArrayObject;
}
