#include "grids.h"
#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>


#include <vector>

using namespace std;
using namespace glm;

grid::grid() {}
grid::~grid()
{
}
;

int grid::createGridArray() {
	
	vector<vec3> gridArray = {
		// position,					texCoord					normal
		glm::vec3(-50.0f,0.0f,-50.0f), glm::vec3(0.0f, 0.0f, 0.0f),vec3(0,1,0),
		glm::vec3(50.0f,0.0f, 50.0f), glm::vec3(1.0f, 1.0f, 0.0f), vec3(0,1,0),
		glm::vec3(50.0f,0.0f, -50.0f), glm::vec3(1.0f, 0.0f, 0.0f),vec3(0,1,0),
																   			 
		glm::vec3(-50.0f,0.0f,-50.0f), glm::vec3(0.0f, 0.0f, 0.0f),vec3(0,1,0),
		glm::vec3(-50.0f,0.0f,50.0f), glm::vec3(0.0f, 1.0f, 0.0f), vec3(0,1,0),
		glm::vec3(50.0f,0.0f, 50.0f), glm::vec3(1.0f, 1.0f, 0.0f), vec3(0,1,0),

	};

	size = gridArray.size()/3;
	GLuint grid_VAO, grid_VBO;
	glGenVertexArrays(1, &grid_VAO);
	glBindVertexArray(grid_VAO);
	glGenBuffers(1, &grid_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, grid_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridArray[0])*gridArray.size(), gridArray.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		3 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(glm::vec3),
		(void*)(sizeof(glm::vec3)*2)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, grid_VBO);
	glBindVertexArray(0);

	return grid_VAO;

}