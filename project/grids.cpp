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

using namespace std;
using namespace glm;

grid::grid() {};

int createGridArray() {
	glm::vec3 gridArray[] = {

			glm::vec3(-1.0f,0.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.9f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.9f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.8f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.8f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.7f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.7f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.6f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.6f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.5f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.5f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.4f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.4f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.3f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.3f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.2f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.2f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.1f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.1f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.1f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.1f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.2f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.2f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.3f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.3f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.4f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.4f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.5f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.5f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.6f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.6f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.7f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.7f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.8f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.8f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.9f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.9f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f,0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.9f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.9f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.8f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.8f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.7f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.7f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.6f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.6f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.4f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.4f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.3f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.3f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.2f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.2f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.1f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.1f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.2f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.2f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.3f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.3f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.4f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.4f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.6f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.6f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.7f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.7f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.8f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.8f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.9f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.9f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),


			glm::vec3(-0.98f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.98f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.88f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.88f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.78f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.78f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.68f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.68f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.58f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.58f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.48f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.48f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.38f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.38f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.28f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.28f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.18f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.18f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.08f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.08f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.08f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.08f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.18f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.18f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.28f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.28f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.38f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.38f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.48f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.48f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.58f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.58f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.68f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.68f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.78f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.78f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.88f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.88f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.98f,0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.98f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f,0.0f,  0.98f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.98f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.88f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.88f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.78f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.78f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.68f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.68f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.58f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.58f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.48f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.48f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.38f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.38f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.28f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.28f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.18f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.18f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f,0.0f,  0.08f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f,0.0f,  0.08f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.08f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.08f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.18f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.18f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.28f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.28f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.38f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.38f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.48f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.48f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.58f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.58f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.68f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.68f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.78f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.78f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.88f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.88f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.98f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.98f), glm::vec3(0.0f, 1.0f, 0.0f),


			glm::vec3(-0.96f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.96f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.86f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.86f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.76f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.76f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.66f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.66f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.56f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.56f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.46f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.46f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.36f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.36f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.26f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.26f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.16f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.16f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.06f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.06f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.06f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.06f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.16f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.16f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.26f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.26f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.36f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.36f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.46f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.46f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.56f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.56f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.66f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.66f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.76f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.76f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.86f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.86f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.96f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.96f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f, 0.0f, 0.96f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.96f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.86f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.86f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.76f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.76f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.66f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.66f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.56f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.56f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.46f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.46f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.36f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.36f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.26f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.26f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.16f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.16f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.06f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.06f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.06f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.06f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.16f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.16f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.26f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.26f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.36f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.36f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.46f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.46f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.56f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.56f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.66f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.66f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.76f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.76f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.86f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.86f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.96f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.96f), glm::vec3(0.0f, 1.0f, 0.0f),



			glm::vec3(-0.94f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.94f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.84f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.84f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.74f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.74f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.64f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.64f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.54f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.54f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.44f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.44f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.34f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.34f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.24f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.24f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.14f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.14f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.04f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.04f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.04f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.04f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.14f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.14f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.24f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.24f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.34f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.34f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.44f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.44f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.54f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.54f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.64f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.64f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.74f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.74f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.84f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.84f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.94f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.94f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f, 0.0f, 0.94f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.94f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.84f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.84f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.74f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.74f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.64f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.64f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.54f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.54f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.44f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.44f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.34f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.34f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.24f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.24f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.14f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.14f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.04f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.04f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.04f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.04f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.14f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.14f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.24f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.24f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.34f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.34f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.44f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.44f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.54f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.54f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.64f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.64f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.74f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.74f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.84f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.84f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.94f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.94f), glm::vec3(0.0f, 1.0f, 0.0f),


			glm::vec3(-0.92f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.92f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.82f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.82f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.72f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.72f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.62f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.62f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.52f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.52f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.42f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.42f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.32f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.32f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.22f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.22f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.12f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.12f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.02f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.02f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.02f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.02f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.12f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.12f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.22f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.22f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.32f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.32f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.42f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.42f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.52f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.52f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.62f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.62f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.72f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.72f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.82f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.82f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.92f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.92f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f, 0.0f, 0.92f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.92f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.82f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.82f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.72f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.72f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.62f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.62f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.52f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.52f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.42f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.42f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.32f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.32f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.22f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.22f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.12f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.12f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.02f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.02f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.02f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.02f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.12f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.12f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.22f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.22f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.32f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.32f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.42f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.42f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.52f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.52f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.62f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.62f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.72f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.72f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.82f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.82f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.92f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.92f), glm::vec3(0.0f, 1.0f, 0.0f),


			glm::vec3(0.00f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.00f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.90f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.90f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.80f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.80f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.70f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.70f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.60f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.60f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.50f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.50f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.40f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.40f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.30f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.30f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.20f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.20f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.10f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.10f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.00f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.00f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.10f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.10f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.20f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.20f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.30f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.30f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.40f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.40f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.50f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.50f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.60f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.60f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.70f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.70f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.80f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.80f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.90f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.90f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.00f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.00f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			glm::vec3(-1.0f, 0.0f, 0.00f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.00f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.90f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.90f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.80f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.80f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.70f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.70f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.60f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.60f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.50f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.50f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.40f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.40f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.30f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.30f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.20f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.20f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.10f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.10f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.00f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.00f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.10f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.10f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.20f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.20f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.30f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.30f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.40f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.40f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.50f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.50f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.60f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.60f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.70f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.70f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.80f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.80f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.90f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.90f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, -0.00f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, -0.00f), glm::vec3(0.0f, 1.0f, 0.0f),
	};
	GLuint grid_VAO, grid_VBO;
	glGenVertexArrays(1, &grid_VAO);
	glBindVertexArray(grid_VAO);
	glGenBuffers(1, &grid_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, grid_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridArray), gridArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, grid_VBO);
	glBindVertexArray(0);

	return grid_VAO;

}