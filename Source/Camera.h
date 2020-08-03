#pragma once


#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
    ~Camera();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewProjectionMatrix();
	//glm::vec3 GetCameraPosition() { return cameraPosition; };

protected:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	
	
	float cameraSpeed = 1.0f;
	float cameraFastSpeed = 3 * cameraSpeed;
	float cameraHorizontalAngle = 90.0f;
	float cameraVerticalAngle = 0.0f;
	float spinningAngle = 0.0f;
};