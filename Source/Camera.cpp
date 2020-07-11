#include "Camera.h"
#include <glm/gtx/transform.hpp>

using namespace glm;

Camera::Camera()
{
}

Camera::~Camera()
{
}

mat4 Camera::GetViewProjectionMatrix() const
{

	mat4 viewProjection(1.0f);

	// Solution
#if 1
	viewProjection = GetProjectionMatrix() * GetViewMatrix();
#endif

	return viewProjection;
}

mat4 Camera::GetProjectionMatrix() const
{
	return perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
};
