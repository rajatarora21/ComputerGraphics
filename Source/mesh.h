#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>


class mesh
{
public:
	mesh();
	virtual ~mesh();
	

	virtual glm::mat4 GetWorldMatrix() const;

	void SetName(std::string name);
	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);

	glm::vec3 GetPosition() const { return mPosition; }
	glm::vec3 GetScaling() const { return mScaling; }
	glm::vec3 GetRotationAxis() const { return mRotationAxis; }

	float     GetRotationAngle() const { return mRotationAngleInDegrees; }

protected:
	std :: string mName;
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;
	glm::vec3 mAngularAxis;
	float     mAngularVelocityInDegrees;
};

