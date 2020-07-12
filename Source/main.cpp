//
// COMP 371 Assignment 1
//
// Created by Nicolas Bergeron on 09/07/2020.

#include "main.h"
#include "Camera.h"
#include "mesh.h"
#include "grids.h"
#include "shaderloader.h"
#include "cube.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
						// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include <iostream>

using namespace std;


int main(int argc, char*argv[])
{
	// Initialize GLFW and OpenGL version
	glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 2.1, to support more hardware
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE );

#endif

	// Create Window and rendering context using GLFW, resolution is 800x600
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - assignment1", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to create GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// rgb (0-255) value / 255

	// Compile and link shaders here ...
	shaderloader* shader = new shaderloader();


	GLuint shaderProgram = shader->getProgramId();

	// Define and upload geometry to the GPU here ...
	cube* cube1 = new cube();
	int vao = cube1->createCubeArray();

	//grid* g = new grid();

	//int vao = g->createGridArray();
	double lastFrameTime = glfwGetTime();


	// Enable Backface culling
	//glEnable(GL_CULL_FACE);
	// Enable z buffer
	//glEnable(GL_DEPTH_TEST);
	// Entering Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Each frame, reset color of each pixel to glClearColor
		glClear(GL_COLOR_BUFFER_BIT );

		//Updata our resources
		// Draw the objects
		// TODO - draw rainbow triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);
		//glBindVertexArray(vao1);
		//
		// procedure for using VAO and VBO
		// before the game loop, initialize the vaos:
		// 1. generate, store and bind a vao
		// 2. generate, store and bind the vbo(s)  xyzxyz rgbrgb stst
		// 3. unbind the vbo and the vaos
		// in the main loop, render:
		// bind vao
		// glDraw*()
		// unbind the vao


		// End frame
		glfwSwapBuffers(window); //render in the background buffer, and display the front buffer withn rendered image

		// Detect inputs
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}
