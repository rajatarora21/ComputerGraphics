//
// COMP 371 Assignment 1
//
// Created by Zhen Long on 09/07/2020.

#include "main.h"
#include "grids.h"
#include "shaderloader.h"
#include "cube.h"
#include "coord.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
						// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

void setViewMatrix(int shader, mat4 viewMatrix)
{
	GLuint viewMatrixLocation = glGetUniformLocation(shader, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void setProjectionMatrix(int shader, mat4 projectionMatrix)
{
	GLuint projectionMatrixLocation = glGetUniformLocation(shader, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}



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
	glUseProgram(shaderProgram);
	// Define and upload geometry to the GPU here ...
	

	//grid* g = new grid();

	

	/*Camera* cam = new Camera();
	mat4 viewMatrix;
	viewMatrix = cam->GetViewMatrix();
	mat4 projectionMatrix;
	projectionMatrix = cam->GetProjectionMatrix();

	setViewMatrix(shaderProgram, viewMatrix);
	setProjectionMatrix(shaderProgram, projectionMatrix);*/

	vec3 cameraPosition(0.2f, 0.3f, 1.0f);
	vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);
	float cameraHorizontalAngle = 90.0f;
	float cameraVerticalAngle = 0.0f;
	float cameraSpeed = 1.0f;

	mat4 projectionMatrix = glm::perspective(45.0f,            // field of view in degrees
		800.0f / 600.0f,  // aspect ratio
		0.01f, 100.0f);   // near and far (near > 0)

	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Set initial view matrix
	mat4 viewMatrix = lookAt(cameraPosition,  // eye
		cameraPosition + cameraLookAt,  // center
		cameraUp); // up

	GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	grid* g = new grid();
	int vao_grid = g->createGridArray();
	cube* cube1 = new cube();
	int vao_cube = cube1->createCubeArray();
	coord* axies = new coord();
	int vao_axis = axies->createAxisArray();

	float factor = 1.0f;
	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	double lastMousePosX, lastMousePosY;
	glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
	GLuint worldmatrixlocation;
	GLuint mode = GL_TRIANGLES;
	mat4 worldMatrix;
	mat4 transformMatrix(1.0f);
	mat4 RotatMatrix(1.0f);
	mat4 center = glm::rotate(mat4(1.0f), glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f)) * glm::translate(mat4(1.0), vec3(-0.34f, 0.0f, 0.52f));
	float moving = 0.0f, raise = 0.0f;
	float degree = 0.0f;

	// Enable Backface culling
	glEnable(GL_CULL_FACE);
	// Enable z buffer
	glEnable(GL_DEPTH_TEST);
	// Entering Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Each frame, reset color of each pixel to glClearColor
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		float dt = glfwGetTime() - lastFrameTime;
		lastFrameTime += dt;

		//draw sujects first name zhen and 3th alphabet E
		// left of E
		glBindVertexArray(vao_cube);
		worldMatrix = RotatMatrix*transformMatrix*center*
			glm::translate(mat4(1.0f), vec3(0.2f, 0.2f, -0.5f)) *
			glm::scale(mat4(1.0f), vec3(0.02f, 0.15f, 0.02f));
		worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
		glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);

		// top of E
		glBindVertexArray(vao_cube);
		worldMatrix = RotatMatrix*transformMatrix*center*
			glm::translate(mat4(1.0f), vec3(0.24f, 0.27f, -0.5f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
			glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
		worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
		glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);
		//mid of E
		glBindVertexArray(vao_cube);
		worldMatrix = RotatMatrix*transformMatrix*center*
			glm::translate(mat4(1.0f), vec3(0.24f, 0.2f, -0.5f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
			glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
		worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
		glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);
		// botom of E
		glBindVertexArray(vao_cube);
		worldMatrix = RotatMatrix*transformMatrix*center*
			glm::translate(mat4(1.0f), vec3(0.24f, 0.12f, -0.5f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
			glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
		worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
		glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);

		// student ID 27117507 and 4th digit is 1
		glBindVertexArray(vao_cube);
		worldMatrix = RotatMatrix*transformMatrix*center*
			glm::translate(mat4(1.0f), vec3(0.4f, 0.19f, -0.5f)) *
			glm::scale(mat4(1.0f), vec3(0.02f, 0.17f, 0.02f));
		worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
		glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);





		//draw grids
		glBindVertexArray(vao_grid);
		mat4 gridWorldMatrix(1.0f);
		worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
		glDrawArrays(GL_LINES, 0, g->getSize()); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);

		//draw axes
		glBindVertexArray(vao_axis);
		glDrawArrays(GL_LINES, 0, 6);
		glBindVertexArray(0);



		// End frame
		glfwSwapBuffers(window); //render in the background buffer, and display the front buffer withn rendered image

		// Detect inputs
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		//left button to zoom in/out with respect to movement

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			double dy = mouseY - lastMousePosY;
			lastMousePosY = mouseY;
			cameraPosition += 0.0009f *(float)dy* cameraLookAt;
			float X = cameraPosition.x;
			float Y = cameraPosition.y;
			float Z = cameraPosition.z;

			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(X, Y, Z),  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up


			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		//scale up and down
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			transformMatrix = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
			factor += 0.0005;
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			if (factor > 0.0005)
			{
				factor -= 0.0005;
				transformMatrix = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
			}
				
		}

		//move the object
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			
			transformMatrix = glm::translate(mat4(1.0f), vec3(0.0+moving, 0.0f+raise, 0.0f));
			moving -= 0.0005;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			
			transformMatrix = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
			moving += 0.0005;
		
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

			transformMatrix = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
			raise += 0.0005;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		
			transformMatrix = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
			raise -= 0.0005;
		}

		// rotate 5 degree about Y axis
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

			RotatMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
			degree += 5.0f;
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

			RotatMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
			degree -= 5.0f;
		}
		// home to reset
		if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
			float X = 0.2f; 
			float Y = 0.3f;
			float Z = 1.0f;
			cameraPosition = glm::vec3(X, Y, Z);
			cameraLookAt = glm::vec3(0.0f, 0.0f, -1.0);
			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(X, Y, Z),  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		// switch render modes
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			mode = GL_POINTS;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			mode = GL_LINES;
		}
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			mode = GL_TRIANGLES;
		}

		// right button, pan with respect to X
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			double dx = mouseX - lastMousePosX;
			lastMousePosX = mouseX;
			glm::vec3 cameraSideVector = glm::cross(cameraLookAt, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::normalize(cameraSideVector);
			cameraLookAt += 0.0009f *(float)dx * cameraSideVector;
			glm::mat4 viewMatrix = glm::lookAt(cameraPosition,  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		//middle button, tilt  with respect to Y
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			double dy = mouseY - lastMousePosY;
			lastMousePosY = mouseY;
			cameraLookAt += 0.0009f *(float)dy * cameraUp;
			glm::mat4 viewMatrix = glm::lookAt(cameraPosition,  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		// Rx and R-x and Ry and R-y movement

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			float X = cameraPosition.x;
			float Y = cameraPosition.y;
			float Z = cameraPosition.z;
			float radius = sqrtf(X * X + Z * Z);
			float degree = atanf(Z / X);
			float dd = 0.001f;
			if (degree + dd < 3.14 / 2 && degree + dd>-3.14 / 2) {

				X = radius * cos(degree + dd);
				Z = radius * sin(degree + dd);
			}
			cameraPosition = glm::vec3(X, Y, Z);
			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(X, Y, Z),  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			float X = cameraPosition.x;
			float Y = cameraPosition.y;
			float Z = cameraPosition.z;
			float radius = sqrtf(X * X + Z * Z);
			float degree = atanf(Z / X);
			float dd = 0.001f;
			if (degree - dd < 3.14 / 2 && degree - dd>-3.14 / 2) {

				X = radius * cos(degree - dd);
				Z = radius * sin(degree - dd);
			}
			cameraPosition = glm::vec3(X, Y, Z);
			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(X, Y, Z),  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			float X = cameraPosition.x;
			float Y = cameraPosition.y;
			float Z = cameraPosition.z;
			float radius = sqrtf(Y * Y + Z * Z);
			float degree = atanf(Z / Y);
			float dd = 0.001f;
			if (degree + dd < 3.14 / 2 && degree + dd>-3.14 / 2) {
				Y = radius * cos(degree + dd);
				Z = radius * sin(degree + dd);
			}
			cameraPosition = glm::vec3(X, Y, Z);
			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(X, Y, Z),  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			float X = cameraPosition.x;
			float Y = cameraPosition.y;
			float Z = cameraPosition.z;
			float radius = sqrtf(Y * Y + Z * Z);
			float degree = atanf(Z / Y);
			float dd = 0.001f;
			if (degree - dd < 3.14 / 2 && degree - dd>-3.14 / 2) {
				Y = radius * cos(degree - dd);
				Z = radius * sin(degree - dd);
			}
			cameraPosition = glm::vec3(X, Y, Z);
			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(X, Y, Z),  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up

			GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		}

	}

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}
