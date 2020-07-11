#include "mesh.h"
#include "World.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;


mesh::mesh() : 
	mName("UNNAMED"), mPosition(0.0f, 0.0f, 0.0f),
	mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f),
	mRotationAngleInDegrees(0.0f),
	mAngularAxis(mRotationAxis), mAngularVelocityInDegrees(0.0f)
{
}



mesh::~mesh()
{
}

void mesh::SetName(string name)
{
	mName = name;
}

glm::mat4 mesh::GetWorldMatrix() const
{
	// @TODO 2 - You must build the world matrix from the position, scaling and rotation informations
	//           If the model has an animation, get the world transform from the animation.
	mat4 worldMatrix(1.0f);

	// Solution TRS

	mat4 t = glm::translate(mat4(1.0f), mPosition);
	mat4 r = glm::rotate(mat4(1.0f), glm::radians(mRotationAngleInDegrees), mRotationAxis);
	mat4 s = glm::scale(mat4(1.0f), mScaling);
	worldMatrix = t * r * s;

	return worldMatrix;
}

void mesh::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

void mesh::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void mesh::SetRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;
}

	
