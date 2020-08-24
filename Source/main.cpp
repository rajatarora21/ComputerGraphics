//
// Yuvraj Singh Athwal(40075586), Rajat Arora(40078146), Zhen Long(27117507), Yiyang Zhou(40046467)
//PA 3
//Lab1, COMP371- https://moodle.concordia.ca/moodle/mod/resource/view.php?id=2306198


//importing required files.
#include "grids.h"
#include "shaderloader.h"
#include "cube.h"
#include "coord.h"
#include "sphere.h"
#include "rubikCube.h"

//initializing OpenGL libraries
#define GLEW_STATIC 1   
#include <GL/glew.h>    

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "main.h"
#include "textRenderer.h"
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

//letter and digit transform data
struct LetterDigitData
{
	vector<mat4> letterMatrices;	//letter's cube transforms
	vector<mat4> digitMatrices;		//digit's cube transforms
	mat4 translation;
	mat4 rotation;
	mat4 scaling;
	mat4 shearing;
	bool continueShearXPos;
	bool continueShearXNeg;
};
bool shadow = true;
LetterDigitData letterDigitDatas[5] = {
	{
		//draw sujects first name zhen and 3th alphabet E
		{
			glm::translate(mat4(1.0f), vec3(-0.06f,0.00f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.15f, 0.02f)), // left of E
			glm::translate(mat4(1.0f), vec3(-0.02f,0.07f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)), //top of E
			glm::translate(mat4(1.0f), vec3(-0.02f,0.00f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)),//mid of E
			glm::translate(mat4(1.0f), vec3(-0.02f,-0.08f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)),//botom of E
		},
		// student ID 27117507 and 4th digit is 1
		{
			glm::translate(mat4(1.0f), vec3(0.14f,-0.01f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.17f, 0.02f)),
		},
		glm::translate(mat4(1.0f), vec3(35.0f,5.0f,-35.0f)),//translation
		mat4(1),//rotation
		glm::scale(mat4(1),vec3(50)),//scaling
		mat4(1),//shearing
		false,
		false,
	},
	{
		//V and 7 for Yuvraj.
		{
			//V
			glm::translate(mat4(1.0f), vec3(-0.11f,-0.03f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f)),
			glm::translate(mat4(1.0f), vec3(-0.05f,-0.03f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(165.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f)),
		},
		{
			// 7
			glm::translate(mat4(1.0f), vec3(0.06f,0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			glm::translate(mat4(1.0f), vec3(0.05f,-0.05f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			// top of 7
			glm::translate(mat4(1.0f), vec3(0.03f,0.06f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)),
		},
		glm::translate(mat4(1.0f), vec3(-35.0f,5.0f,35.0f)),//translation
		mat4(1),//rotation
		glm::scale(mat4(1),vec3(50)),//scaling
		mat4(1),//shearing
		false,
		false,
	},
	/*
	{
		//V and 1 for Divyluv
		{
			//V
			glm::translate(mat4(1.0f), vec3(-0.06f,-0.00f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f)),
			glm::translate(mat4(1.0f), vec3(0.00f,-0.00f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(165.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.18f, 0.02f)),
		},
		{
			//1
			glm::translate(mat4(1.0f), vec3(0.06f,0.01f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.17f, 0.02f)),
		},
		glm::translate(mat4(1.0f), vec3(-35.0f,5.0f,-35.0f)),//translation
		mat4(1),//rotation
		glm::scale(mat4(1),vec3(50)),//scaling
		mat4(1),//shearing
		false,
		false,
	},
	*/
	{
		//Y and 4 for Yiyang
		{
			glm::translate(mat4(1.0f), vec3(-0.14f,0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			glm::translate(mat4(1.0f), vec3(-0.11f,-0.05f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			glm::translate(mat4(1.0f), vec3(-0.08f,0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
		},
		//4
		{
			glm::translate(mat4(1.0f), vec3(0.11f,0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			//mid of 4
			glm::translate(mat4(1.0f), vec3(0.07f,-0.01f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)),
			// top right of 4
			glm::translate(mat4(1.0f), vec3(0.01f,0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			//bottom right
			glm::translate(mat4(1.0f), vec3(0.11f,-0.05f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
		},
		glm::translate(mat4(1.0f), vec3(35.0f,5.0f,35.0f)),//translation
		mat4(1),//rotation
		glm::scale(mat4(1),vec3(50)),//scaling
		mat4(1),//shearing
		false,
		false,
	},
	{
		//J and 7 for Rajat
		{
			glm::translate(mat4(1.0f), vec3(-0.12f,-0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			// botom of J
			glm::translate(mat4(1.0f), vec3(-0.07f,-0.06f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)),
			// top right of J
			glm::translate(mat4(1.0f), vec3(-0.02f,0.05f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			// bottom right of J
			glm::translate(mat4(1.0f), vec3(-0.02f,-0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
		},
		{
			// 7
			glm::translate(mat4(1.0f), vec3(0.08f,0.05f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			glm::translate(mat4(1.0f), vec3(0.07f,-0.03f,0.00f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.08f, 0.02f)),
			// top of 7
			glm::translate(mat4(1.0f), vec3(0.05f,0.08f,0.00f))*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(mat4(1.0f), vec3(0.02f, 0.1f, 0.02f)),
		},
		glm::translate(mat4(1.0f), vec3(-35.0f,5.0f,-35.0f)),//translation
		mat4(1),//rotation
		glm::scale(mat4(1),vec3(50)),//scaling
		mat4(1),//shearing
		false,
		false,
	},
};

int editingModelId = -1;
int editModelIndex = -1;
RubikCube rubikCube;
float playTime = 0;
bool playing = false;
TextRenderer timeText;

void keyCallback(GLFWwindow *window, int keyCody, int scan,int action, int mods)
{
	if (!mods&&action==GLFW_PRESS)
	{
		if (editingModelId >= 0 && editingModelId<5)
		{
			if (keyCody == 'G')
			{
				letterDigitDatas[editingModelId].continueShearXPos = !letterDigitDatas[editingModelId].continueShearXPos;
				letterDigitDatas[editingModelId].continueShearXNeg = false;
				for (size_t i = 0; i < 5; i++)
				{
					if (i != editingModelId)
					{
						letterDigitDatas[i].continueShearXNeg = false;
						letterDigitDatas[i].continueShearXPos = false;
					}
				}
			}
			if (keyCody == 'H')
			{
				letterDigitDatas[editingModelId].continueShearXNeg = !letterDigitDatas[editingModelId].continueShearXNeg;
				letterDigitDatas[editingModelId].continueShearXPos = false;
				for (size_t i = 0; i < 5; i++)
				{
					if (i != editingModelId)
					{
						letterDigitDatas[i].continueShearXNeg = false;
						letterDigitDatas[i].continueShearXPos = false;
					}
				}
			}
		}

		if (keyCody>='1'&&keyCody<='5')
		{
			editingModelId = keyCody - '1';
		}
	}

	if (action == GLFW_PRESS)
	{
		if (editModelIndex == -1)
		{
			if (keyCody == 'A') {
				rubikCube.makeMove(RubikCube::L, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS);
			}
			if (keyCody == 'D') {
				rubikCube.makeMove(RubikCube::R, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS);
			}
			if (keyCody == 'W') {
				rubikCube.makeMove(RubikCube::U, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS);
			}
			if (keyCody == 'S') {
				rubikCube.makeMove(RubikCube::D, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS);
			}
			if (keyCody == 'Q') {
				rubikCube.makeMove(RubikCube::F, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS);
			}
			if (keyCody == 'E') {
				rubikCube.makeMove(RubikCube::B, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS);
			}
			if (keyCody==' ')
			{
 				playing = !playing;
			}
		}
	}

}

GLuint loadTexture(const char *file)
{
	GLuint tex=0;
	int w, h;
	unsigned char *pixels = stbi_load(file, &w, &h, 0, 4);
	if (pixels)
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		free(pixels);
	}
	return tex;
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

	// Create Window, resolution is 1024x768
	GLFWwindow* window = glfwCreateWindow(1024, 768, "PA3", NULL, NULL);
	
	glfwSetKeyCallback(window, keyCallback);
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
	GLuint textureLitProgram;
	GLuint unlitProgram;
	GLuint depthProgram;
	GLuint fontProgram;

	GLuint currentProgram;

#if defined(PLATFORM_OSX)
	std::string shaderPathPrefix = "Shaders/";
#else
	std::string shaderPathPrefix = "../Assets/Shaders/";
#endif
	unlitProgram = shaderloader::LoadShaders(shaderPathPrefix + "vertex_shader_color.glsl", shaderPathPrefix + "fragment_shader_color.glsl");
	textureLitProgram = shaderloader::LoadShaders(shaderPathPrefix + "vertex_shader.glsl", shaderPathPrefix + "fragment_shader.glsl");
	depthProgram = shaderloader::LoadShaders(shaderPathPrefix + "vertex_depth.glsl", shaderPathPrefix + "fragment_depth.glsl");
	fontProgram= shaderloader::LoadShaders(shaderPathPrefix + "font_vert.glsl", shaderPathPrefix + "font_frag.glsl");

	vec3 cameraPosition(0.0f, 50.0f, 80.0f);
	vec3 cameraLookAt(0.0f, -5.0f, -8.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);
	float cameraSpeed = 1.0f;

	grid* g = new grid();
	int vao_grid = g->createGridArray();
	cube* cube1 = new cube();
	int vao_cube = cube1->createCubeArray();
	coord* axies = new coord();
	int vao_axis = axies->createAxisArray();
	sphere* ball = new sphere();
	int vao_ball = ball->createSphereArray();

	rubikCube.initialize();
	rubikCube.model = translate(mat4(1), vec3(0, 10, 0))*scale(mat4(1), vec3(5, 5, 5));
	rubikCube.setCubeTexture(loadTexture("../Assets/Textures/cube.bmp"));
	rubikCube.setFaceTexture({
		loadTexture("../Assets/Textures/face1.png"),
		loadTexture("../Assets/Textures/movie.jpg"),
		loadTexture("../Assets/Textures/face6.png"),
		loadTexture("../Assets/Textures/music.jpg"),
		loadTexture("../Assets/Textures/face2.png"),
		loadTexture("../Assets/Textures/game.jpg"),
	});


	GLuint grassTex = loadTexture("../Assets/Textures/grass.jpg");
	GLuint boxTex = loadTexture("../Assets/Textures/crate.jpg");
	GLuint metalTex = loadTexture("../Assets/Textures/metal.jpg");
	GLuint ballTex = loadTexture("../Assets/Textures/bubble.png");

	timeText.setFontTexture(loadTexture("../Assets/Textures/ascii.png"));

	auto err = glGetError();

	//depth render target
	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	//frame buffer
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
	glDrawBuffer(GL_NONE);
	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status !=GL_FRAMEBUFFER_COMPLETE)
	{
		printf("fbo error!");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	double lastMousePosX, lastMousePosY;
	glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
	GLuint worldmatrixlocation;
	GLuint mode = GL_TRIANGLES;
	mat4 worldMatrix=mat4(1);


	mat4 center = glm::rotate(mat4(1.0f), glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f)) * glm::translate(mat4(1.0), vec3(-0.34f, 0.0f, 0.52f));
	float moving = 0.0f, raise = 0.0f;
	float degree = 0.0f;

	// Enable Backface culling
	glEnable(GL_CULL_FACE);
	// Enable z buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	// Entering Main Loop

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	while (!glfwWindowShouldClose(window))
	{
		float dt = glfwGetTime() - lastFrameTime;
		lastFrameTime += dt;

		rubikCube.update(dt);

		if (playing)
		{
			playTime += dt;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		double dx = mouseX - lastMousePosX;
		double dy = mouseY - lastMousePosY;
		lastMousePosX = mouseX;
		lastMousePosY = mouseY;

		//update model shearing
		for (size_t i = 0; i < 5; i++)
		{
			if (letterDigitDatas[i].continueShearXPos)
			{
				mat4 shearing = mat4(
					1, 0, 0, 0,
					0.1*dt, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
				letterDigitDatas[i].shearing = letterDigitDatas[i].shearing*shearing;
			}
			if (letterDigitDatas[i].continueShearXNeg)
			{
				mat4 shearing = mat4(
					1, 0, 0, 0,
					-0.1*dt, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
				letterDigitDatas[i].shearing = letterDigitDatas[i].shearing*shearing;
			}
		}


		mat4 lightVP;
		//shadow pass
		{
			glClearDepth(1);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glViewport(0, 0, 1024, 1024);
			glClear(GL_DEPTH_BUFFER_BIT);
			currentProgram = depthProgram;
			glUseProgram(depthProgram);
			mat4 projection = perspective<float>(radians(160.0f), 1.0f, 0.1f, 50);

			vec4 lightPos = vec4(0, 30, 0, 1);
			vec4 lightDir = vec4(0, -1, 0, 0);
			vec4 lightUp = vec4(1, 0, 0, 0);

			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(2, 2);

			mat4 view = lookAt(vec3(worldMatrix*lightPos),  // eye
				vec3(worldMatrix*lightPos)+ vec3(worldMatrix*lightDir),  // center
				vec3(worldMatrix*lightUp)); // up
			setProjectionMatrix(currentProgram, projection);
			setViewMatrix(currentProgram, view);
			if (shadow)
				lightVP = projection * view;
			else
				lightVP = worldMatrix;
			for (auto &data : letterDigitDatas)
			{
				glBindTexture(GL_TEXTURE_2D, boxTex);
				for (auto &m : data.letterMatrices)
				{
					glBindVertexArray(vao_cube);
					mat4 modelMatrix = worldMatrix * data.translation * data.rotation *data.scaling*data.shearing*m;
					worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
					glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &modelMatrix[0][0]);
					glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
					glBindVertexArray(0);
				}
				glBindTexture(GL_TEXTURE_2D, metalTex);
				for (auto &m : data.digitMatrices)
				{
					glBindVertexArray(vao_cube);
					mat4 modelMatrix = worldMatrix * data.translation * data.rotation *data.scaling*data.shearing*m;
					worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
					glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &modelMatrix[0][0]);
					glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
					glBindVertexArray(0);
				}
			}

			//draw rubik cube
			rubikCube.render(currentProgram, worldMatrix);

			//draw grids
			glBindVertexArray(vao_grid);
			mat4 gridWorldMatrix = worldMatrix * mat4(1);
			worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, g->getSize()); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glDisable(GL_POLYGON_OFFSET_FILL);
		}

		int width;
		int height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// Each frame, reset color of each pixel to glClearColor
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentProgram = textureLitProgram;
		glUseProgram(currentProgram);

		mat4 projection = perspective<float>(radians(60.0f), float(width) / height, 0.01f, 500);
		mat4 view = lookAt(cameraPosition,  // eye
			cameraPosition + cameraLookAt,  // center
			cameraUp); // up
		setProjectionMatrix(currentProgram, projection);
		setViewMatrix(currentProgram, view);

		GLuint viewMatrixLocation = glGetUniformLocation(currentProgram, "lightTransformMatrix");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);


		int lightVPLoc = glGetUniformLocation(currentProgram, "lightVP");
		int texLoc = glGetUniformLocation(currentProgram, "tex");
		int shadiwTexLoc = glGetUniformLocation(currentProgram, "shadowTex");
		int roughnessLoc = glGetUniformLocation(currentProgram, "roughness");

		glUniform1i(texLoc, 0);
		glUniform1i(shadiwTexLoc, 1);
		glUniformMatrix4fv(lightVPLoc,1,GL_FALSE,value_ptr(lightVP));

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTex);

		//draw letter and digit
		for (auto &data : letterDigitDatas)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, boxTex);
			for (auto &m : data.letterMatrices)
			{
				glBindVertexArray(vao_cube);
				mat4 modelMatrix = worldMatrix * data.translation * data.rotation *data.scaling*data.shearing*m;
				worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
				glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &modelMatrix[0][0]);
				glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
				glBindVertexArray(0);
			}

			glUniform1f(roughnessLoc, 0.0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, metalTex);
			for (auto &m : data.digitMatrices)
			{
				glBindVertexArray(vao_cube);
				mat4 modelMatrix = worldMatrix * data.translation * data.rotation *data.scaling*data.shearing*m;
				worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
				glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &modelMatrix[0][0]);
				glDrawArrays(mode, 0, 36); // 3 vertices, starting at vertex array index 0
				glBindVertexArray(0);
			}
			glUniform1f(roughnessLoc, 1.0);
		}


		//draw rubik's cube
		rubikCube.render(currentProgram, worldMatrix);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, grassTex);
		//draw grids
		glBindVertexArray(vao_grid);
		mat4 gridWorldMatrix = worldMatrix * mat4(1);
		worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &gridWorldMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, g->getSize()); // 3 vertices, starting at vertex array index 0
		glBindVertexArray(0);


		currentProgram = unlitProgram;
		glUseProgram(currentProgram);
		setProjectionMatrix(currentProgram, projection);
		setViewMatrix(currentProgram, view);
		//draw axes
		mat4 axisWorldMatrix = worldMatrix * mat4(1);
		glLineWidth(5);
		worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
		glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &axisWorldMatrix[0][0]);
		glBindVertexArray(vao_axis);
		glDrawArrays(GL_LINES, 0, 6);
		glBindVertexArray(0);
		glLineWidth(1);

		//draw bubble
		currentProgram = textureLitProgram;
		glUseProgram(currentProgram);

		for (auto &data : letterDigitDatas)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);

			//draw ball
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ballTex);
			glBindVertexArray(vao_ball);
			mat4 modelMatrix = worldMatrix * data.translation * data.rotation *data.scaling*data.shearing*translate(mat4(1), vec3(0, 0.2, 0))*scale(mat4(1), vec3(0.2));
			worldmatrixlocation = glGetUniformLocation(currentProgram, "worldMatrix");
			glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &modelMatrix[0][0]);
			glDrawArrays(mode, 0, ball->getSize()); // 3 vertices, starting at vertex array index 0
			glBindVertexArray(0);

			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);

		}

		//render text
		currentProgram = fontProgram;
		glUseProgram(currentProgram);
		setProjectionMatrix(currentProgram, ortho<float>(0, width, 0, height, -100, 100));
		timeText.setPosition({ 50,height - 50 });
		char text[256] = "";
		sprintf(text, "TIME:%.02fs", playTime);
		timeText.setPosition({ 50,height - 50 });
		timeText.setText(text);
		timeText.render(currentProgram);



		// End frame
		glfwSwapBuffers(window); //render in the background buffer, and display the front buffer withn rendered image

		// Detect inputs
		glfwPollEvents();
		editModelIndex = -1;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			editModelIndex = 0;
		}
		else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			editModelIndex = 1;
		}
		else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			editModelIndex = 2;
		}
		else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			editModelIndex = 3;
		}
		else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		{
			editModelIndex = 4;
		}

		if (editModelIndex>=0&& editModelIndex<5)
		{
			//scale up and down
			if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].scaling = glm::scale(letterDigitDatas[editModelIndex].scaling, vec3(1.01, 1.01, 1.01));
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				letterDigitDatas[editModelIndex].scaling = glm::scale(letterDigitDatas[editModelIndex].scaling, vec3(1/1.01, 1 / 1.01, 1 / 1.01));
			}

			//move the object
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].translation = glm::translate(letterDigitDatas[editModelIndex].translation, vec3(-0.05f, 0.0f, 0.0f));
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].translation = glm::translate(letterDigitDatas[editModelIndex].translation, vec3(0.05f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].translation = glm::translate(letterDigitDatas[editModelIndex].translation, vec3( 0.0f, 0.05f,0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].translation = glm::translate(letterDigitDatas[editModelIndex].translation, vec3(0.0f, -0.05f, 0.0f));
			}

			// rotate 5 degree about Y axis
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].rotation = glm::rotate(letterDigitDatas[editModelIndex].rotation, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
				letterDigitDatas[editModelIndex].rotation = glm::rotate(letterDigitDatas[editModelIndex].rotation, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			}

			// rotate 5 degree about X axis
			if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {

				letterDigitDatas[editModelIndex].rotation = glm::rotate(letterDigitDatas[editModelIndex].rotation, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			}

			if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
				letterDigitDatas[editModelIndex].rotation = glm::rotate(letterDigitDatas[editModelIndex].rotation, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			}

			// shearing
			if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
				mat4 shearing = mat4(
					1, 0, 0, 0,
					0.05, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
				letterDigitDatas[editModelIndex].shearing = letterDigitDatas[editModelIndex].shearing*shearing;
			}

			if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
				mat4 shearing = mat4(
					1, 0, 0, 0,
					-0.05, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
				letterDigitDatas[editModelIndex].shearing = letterDigitDatas[editModelIndex].shearing*shearing;
			}
		}

		// left button, zoom
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			cameraPosition += cameraLookAt*(float)dy*0.1f;
		}

		// right button, pan with respect to X
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			glm::vec3 cameraSideVector = glm::cross(cameraLookAt, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::normalize(cameraSideVector);
			cameraLookAt += 0.009f *(float)dx * cameraSideVector;
			glm::mat4 viewMatrix = glm::lookAt(cameraPosition,  // eye
				cameraPosition + cameraLookAt,  // center
				glm::vec3(0.0f, 1.0f, 0.0f));// up
		}

		//middle button, tilt  with respect to Y
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			double dy = mouseY - lastMousePosY;
			lastMousePosY = mouseY;
			cameraLookAt += 0.009f *(float)dy * cameraUp;
		}

		// Rx and R-x and Ry and R-y world rotation
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			worldMatrix = rotate(mat4(1), 0.1f, vec3(0, 1, 0))*worldMatrix;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			worldMatrix = rotate(mat4(1), 0.1f, vec3(0, -1, 0))*worldMatrix;
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			worldMatrix = rotate(mat4(1), 0.1f, vec3(1, 0, 0))*worldMatrix;
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			worldMatrix = rotate(mat4(1), 0.1f, vec3(-1, 0, 0))*worldMatrix;
		}
		// home to reset
		if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
			cameraPosition = vec3(0.0f, 50.0f, 80.0f);
			cameraLookAt = vec3(0.0f, -5.0f, -8.0f);

			worldMatrix = mat4(1);
		}
		// launch timer
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			playing = true;
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			worldMatrix=mat4(1);
			rubikCube.reset();
			playTime = 0;
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

		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			if (shadow)
				shadow = false;
			else
				shadow = true;
		}



	}

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}
