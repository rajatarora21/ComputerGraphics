#include "Camera.h"
#include <glm/gtx/transform.hpp>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

using namespace glm;

Camera::Camera()
{
	 vec3 cameraPosition(0.0f, 1.0f, -2.0f);
	 vec3 cameraLookAt(0.0f, 0.0f, 0.0f);
	 vec3 cameraUp(0.0f, 1.0f, 0.0f);
	 projectionMatrix = glm::perspective(45.0f,            // field of view in degrees
		800.0f / 600.0f,  // aspect ratio
		0.01f, 100.0f);   // near and far (near > 0)

	 viewMatrix = lookAt(cameraPosition,  // eye
		cameraPosition + cameraLookAt,  // center
		cameraUp); // up
}

Camera::~Camera()
{
}

mat4 Camera::GetViewProjectionMatrix()
{

	mat4 viewProjection(1.0f);

	// Solution
#if 1
	viewProjection = GetProjectionMatrix() * GetViewMatrix();
#endif

	return viewProjection;
}

mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
};

mat4 Camera::GetViewMatrix() 
{
	return viewMatrix;
}