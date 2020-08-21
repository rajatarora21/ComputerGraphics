#include <GL/glew.h>    

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>
#include <functional>

class RubikCube
{
	enum FaceDir
	{
		X=0,
		_X,
		Y,
		_Y,
		Z,
		_Z,
	};
	struct Face
	{
		GLuint vao;
		FaceDir faceDir;
	};
	struct Cube
	{
		glm::mat4 translation;
		glm::mat4 rotation;
		glm::mat4 originalRotation;
		std::vector<Face> faces;
		GLuint vao;
	};

	std::vector<Cube*> cubes;

	struct MoveData
	{
		bool valid=false;
		std::vector<Cube*> moveCubes;
		float moveTime;
		glm::vec3 rotateAxis;
	} currentMove;

	std::vector<Cube *> findCubesOfLayer(std::function<bool(glm::vec3)> pred);

	GLuint createCubeVAO();
	GLuint createFaceVAO(FaceDir faceDir,int tileX,int tileY);

	std::vector<GLuint> faceTextures;
	GLuint cubeTexture;
public:
	enum Move
	{
		_None=-1,
		L=0,	//left
		R,	//right
		U,
		D,
		F,
		B,
	};
	glm::mat4 model;

	float moveTime=0.2;

	void update(float dt);
	void makeMove(Move move,bool cw);

	void initialize();
	void render(GLuint shader,glm::mat4 worldMatrix);
	void setFaceTexture(std::vector<GLuint> faceTex);
	void setCubeTexture(GLuint cubeTex);
};