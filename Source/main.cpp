//
// Yuvraj Singh Athwal(40075586), Rajat Arora(40078146), Zhen Long(27117507), Yiyang Zhou(), Divyluv Sharma(40014962)
//PA 1
//Lab1, COMP371- https://moodle.concordia.ca/moodle/mod/resource/view.php?id=2306198


//importing required files.
#include "grids.h"
#include "shaderloader.h"
#include "cube.h"
#include "coord.h"

//initializing OpenGL libraries
#define GLEW_STATIC 1   
#include <GL/glew.h>    

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

//viewMatrix
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

//main function

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

	// Create Window, resolution is 1024x768
	GLFWwindow* window = glfwCreateWindow(1024, 768, "PA1", NULL, NULL);
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





	// Shaders
	shaderloader* shader = new shaderloader();
	GLuint shaderProgram = shader->getProgramId();
	glUseProgram(shaderProgram);


	vec3 cameraPosition(1.2f, 0.3f, 1.2f);
	vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);
	float cameraHorizontalAngle = 60.0f;
	float cameraVerticalAngle = 0.0f;
	float cameraSpeed = 1.0f;

	mat4 projectionMatrix = glm::perspective(15.0f,            // field of view in degrees
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
	int vao_E = cube1->createCubeArray();
	int vao_V = cube1->createCubeArray();
	int vao_V2 = cube1->createCubeArray();
	int vao_Y = cube1->createCubeArray();
	int vao_cube_J = cube1->createCubeArray();
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
	mat4 transformMatrix_1(1.0f);
	mat4 transformMatrix_2(1.0f);
	mat4 transformMatrix_3(1.0f);
	mat4 transformMatrix_4(1.0f);
	mat4 transformMatrix_5(1.0f);


	mat4 RotatMatrix_1(1.0f);
	mat4 RotatMatrix_2(1.0f);
	mat4 RotatMatrix_3(1.0f);
	mat4 RotatMatrix_4(1.0f);
	mat4 RotatMatrix_5(1.0f);


	mat4 center = glm::rotate(mat4(1.0f), glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f)) * glm::translate(mat4(1.0), vec3(-0.34f, 0.0f, 0.52f));
	float moving = 0.0f, raise = 0.0f;
	float degree = 0.0f;

	// Enable Backface culling
	glEnable(GL_CULL_FACE);
	// Enable z buffer
	glEnable(GL_DEPTH_TEST);
	// Entering Main Loop

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		// Each frame, reset color of each pixel to glClearColor
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float dt = glfwGetTime() - lastFrameTime;
		lastFrameTime += dt;

		//draw sujects first name zhen and 3th alphabet E
		{
			// left of E
			glBindVertexArray(vao_E);
			worldMatrix = RotatMatrix_1 * transformMatrix_1*center*
				glm::translate(mat4(1.0f), vec3(0.2f, 0.2f, -0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.15f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			// top of E
			glBindVertexArray(vao_E);
			worldMatrix = RotatMatrix_1 * transformMatrix_1*center*
				glm::translate(mat4(1.0f), vec3(0.24f, 0.27f, -0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);
			//mid of E
			glBindVertexArray(vao_E);
			worldMatrix = RotatMatrix_1 * transformMatrix_1*center*
				glm::translate(mat4(1.0f), vec3(0.24f, 0.2f, -0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);
			// botom of E
			glBindVertexArray(vao_E);
			worldMatrix = RotatMatrix_1 * transformMatrix_1*center*
				glm::translate(mat4(1.0f), vec3(0.24f, 0.12f, -0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			// student ID 27117507 and 4th digit is 1
			glBindVertexArray(vao_E);
			worldMatrix = RotatMatrix_1 * transformMatrix_1*center*
				glm::translate(mat4(1.0f), vec3(0.4f, 0.19f, -0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.17f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);
		}








		//V and 7 for Yuvraj.
		{

			//V
			glBindVertexArray(vao_V);
			worldMatrix = RotatMatrix_2 * transformMatrix_2*center*
				glm::translate(mat4(1.0f), vec3(-0.74f, 0.18f, 0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			glBindVertexArray(vao_V);
			worldMatrix = RotatMatrix_2 * transformMatrix_2*center*
				glm::translate(mat4(1.0f), vec3(-0.68f, 0.18f, 0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(165.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);



			// 7
			glBindVertexArray(vao_V);
			worldMatrix = RotatMatrix_2 * transformMatrix_2*center*
				glm::translate(mat4(1.0f), vec3(-0.57f, 0.24f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);


			glBindVertexArray(vao_V);
			worldMatrix = RotatMatrix_2 * transformMatrix_2*center*
				glm::translate(mat4(1.0f), vec3(-0.58f, 0.16f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			// top of 7
			glBindVertexArray(vao_V);
			worldMatrix = RotatMatrix_2 * transformMatrix_2*center*
				glm::translate(mat4(1.0f), vec3(-0.6f, 0.27f, 0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);
		}



		//V and 1 for Divyluv
		{
			//V
			glBindVertexArray(vao_V2);
			worldMatrix = RotatMatrix_3 * transformMatrix_3*center*
				glm::translate(mat4(1.0f), vec3(-0.74f, 0.18f, -1.3f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			glBindVertexArray(vao_V2);
			worldMatrix = RotatMatrix_3 * transformMatrix_3*center*
				glm::translate(mat4(1.0f), vec3(-0.68f, 0.18f, -1.3f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(165.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			//1
			glBindVertexArray(vao_V2);
			worldMatrix = RotatMatrix_3 * transformMatrix_3*center*
				glm::translate(mat4(1.0f), vec3(-0.62f, 0.19f, -1.3f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.17f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

		}






		
		//Y and 4 for Yiyang
		{
			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.1f, 0.24f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);


			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.13f, 0.16f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);
			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.16f, 0.24f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			//4

			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.35f, 0.24f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36);
			glBindVertexArray(0);




			//mid of 4
			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.31f, 0.2f, 0.5f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36);
			glBindVertexArray(0);




			// top right of 4
			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.25f, 0.24f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36);
			glBindVertexArray(0);
			//bottom right
			glBindVertexArray(vao_Y);
			worldMatrix = RotatMatrix_4 * transformMatrix_4*center*
				glm::translate(mat4(1.0f), vec3(1.35f, 0.16f, 0.5f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36);
			glBindVertexArray(0);


		}


		//J and 7 for Rajat
		{
			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(0.9f, 0.16f, -1.3f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);




			// botom of J
			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(0.95f, 0.13f, -1.3f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);





			// top right of J
			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(1.0f, 0.24f, -1.3f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36);
			glBindVertexArray(0);


			// bottom right of J
			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(1.0f, 0.16f, -1.3f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36);
			glBindVertexArray(0);

			// 7
			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(1.1f, 0.24f, -1.3f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);


			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(1.09f, 0.16f, -1.3f)) *
				glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			// top of 7
			glBindVertexArray(vao_cube_J);
			worldMatrix = RotatMatrix_5 * transformMatrix_5*center*
				glm::translate(mat4(1.0f), vec3(1.07f, 0.27f, -1.3f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f));
			worldmatrixlocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &worldMatrix[0][0]);
			glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);


		}









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

		//when 1 is pressed		
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
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

				transformMatrix_1 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				factor += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				if (factor > 0.0005)
				{
					factor -= 0.0005;
					transformMatrix_1 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				}



			}

			//move the object
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

				transformMatrix_1 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving -= 0.0005;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

				transformMatrix_1 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving += 0.0005;

			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

				transformMatrix_1 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

				transformMatrix_1 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise -= 0.0005;
			}

			// rotate 5 degree about Y axis
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

				RotatMatrix_1 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
				degree += 5.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

				RotatMatrix_1 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
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



		}

		//when 2 is pressed
		else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
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

				transformMatrix_2 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				factor += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				if (factor > 0.0005)
				{
					factor -= 0.0005;
					transformMatrix_2 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				}



			}

			//move the object
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

				transformMatrix_2 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving -= 0.0005;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

				transformMatrix_2 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving += 0.0005;

			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

				transformMatrix_2 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

				transformMatrix_2 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise -= 0.0005;
			}

			// rotate 5 degree about Y axis
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

				RotatMatrix_2 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
				degree += 5.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

				RotatMatrix_2 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
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

		}
		//When 3 is pressed
		else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
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

				transformMatrix_3 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				factor += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				if (factor > 0.0005)
				{
					factor -= 0.0005;
					transformMatrix_3 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				}



			}

			//move the object
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

				transformMatrix_3 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving -= 0.0005;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

				transformMatrix_3 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving += 0.0005;

			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

				transformMatrix_3 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

				transformMatrix_3 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise -= 0.0005;
			}

			// rotate 5 degree about Y axis
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

				RotatMatrix_3 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
				degree += 5.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

				RotatMatrix_3 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
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


		}

		//when 4 is pressed
		else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
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

				transformMatrix_4 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				factor += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				if (factor > 0.0005)
				{
					factor -= 0.0005;
					transformMatrix_4 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				}



			}

			//move the object
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

				transformMatrix_4 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving -= 0.0005;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

				transformMatrix_4 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving += 0.0005;

			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

				transformMatrix_4 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

				transformMatrix_4 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise -= 0.0005;
			}

			// rotate 5 degree about Y axis
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

				RotatMatrix_4 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
				degree += 5.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

				RotatMatrix_4 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
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


		}

		//when 5 is pressed
		else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
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

				transformMatrix_5 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				factor += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				if (factor > 0.0005)
				{
					factor -= 0.0005;
					transformMatrix_5 = glm::scale(mat4(1.0f), vec3(1.0*factor, 1.0*factor, 1.0*factor));
				}



			}

			//move the object
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

				transformMatrix_5 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving -= 0.0005;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

				transformMatrix_5 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				moving += 0.0005;

			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

				transformMatrix_5 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise += 0.0005;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

				transformMatrix_5 = glm::translate(mat4(1.0f), vec3(0.0 + moving, 0.0f + raise, 0.0f));
				raise -= 0.0005;
			}

			// rotate 5 degree about Y axis
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

				RotatMatrix_5 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
				degree += 5.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

				RotatMatrix_5 = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
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

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
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

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
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

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
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

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
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





	}

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}
