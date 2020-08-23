#include "rubikCube.h"
using namespace glm;
using namespace std;

std::vector<RubikCube::Cube*> RubikCube::findCubesOfLayer(function<bool(glm::vec3)> pred)
{
	std::vector<RubikCube::Cube*> layerOfCubes;
	for (auto c:cubes)
	{
		mat4 m = c->rotation* c->translation;
		vec3 center = m*vec4(0, 0, 0, 1);
		if (pred(center))
		{
			layerOfCubes.push_back(c);
		}
	}
	return layerOfCubes;
}

GLuint RubikCube::createCubeVAO()
{
	// Cube model
	glm::vec3 vertexArray[] = {
		// position,					texCoord						normal
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(-1,0,0), //left
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(-1,0,0),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(-1,0,0),

		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(-1,0,0),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(-1,0,0),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(-1,0,0),

		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(0,0,-1), // far
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,-1),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0,0,-1),

		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(0,0,-1),
		glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0,0,-1),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,-1),

		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(0,-1,0), // bottom
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,-1,0),
		glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0,-1,0),

		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0,-1,0),
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0,-1,0),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,-1,0),

		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0,0,1), // near
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,1),
		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0,0,1),

		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(0,0,1),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0,0,1),
		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0,0,1),

		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(1,0,0),  // right
		glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0),
		glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(1,0,0),

		glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0),
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(1,0,0),
		glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(1,0,0),

		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(0,1,0), // top
		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0,1,0),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0),

		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),glm::vec3(0,1,0),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0,1,0),
	};


	// Create a vertex array
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(vec3),
		(void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(vec3),
		(void*)(sizeof(vec3) * 2)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindVertexArray(0);

	return vertexArrayObject;

}

GLuint RubikCube::createFaceVAO(FaceDir faceDir, int tileX, int tileY)
{
	float faceRatio = 0.9;
	float sp = 0.51;
	vec4 normal = vec4(0, 1, 0,0);
	vec4 pos[] = {
		vec4(-0.5*faceRatio,sp,-0.5*faceRatio,1),
		vec4(0.5*faceRatio,sp,-0.5*faceRatio,1),
		vec4(0.5*faceRatio,sp,0.5*faceRatio,1),
		vec4(-0.5*faceRatio,sp,0.5*faceRatio,1),
	};
	float ts = 1 / 3.0;
	vec3 uv[] = {
		vec3(-0.5,-0.5,1),
		vec3(0.5,-0.5,1),
		vec3(0.5,0.5,1),
		vec3(-0.5,0.5,1),
	};

	mat4 posNormM=mat4(1);
	switch (faceDir)
	{
	case RubikCube::X:
		posNormM = mat4(0,-1,0,0,1,0,0,0,0,0,1,0,0,0,0,1);
		break;
	case RubikCube::_X:
		posNormM = mat4(0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		break;
	case RubikCube::Y:
		break;
	case RubikCube::_Y:
		posNormM = mat4(-1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		break;
	case RubikCube::Z:
		posNormM = mat4(1, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 1);
		break;
	case RubikCube::_Z:
		posNormM = mat4(1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1);
		break;
	default:
		break;
	}

	mat3 uvM=mat3(ts*faceRatio,0,0,0, ts*faceRatio,0,(tileX+0.5)*ts,(tileY+0.5)*ts,1);

	// Cube model
	glm::vec3 vertexArray[] = {
		// position,					texCoord						normal
		glm::vec3(posNormM*pos[0]), uvM*uv[0],glm::vec3(posNormM*normal), //left
		glm::vec3(posNormM*pos[2]), uvM*uv[2],glm::vec3(posNormM*normal), //left
		glm::vec3(posNormM*pos[1]), uvM*uv[1],glm::vec3(posNormM*normal), //left

		glm::vec3(posNormM*pos[0]), uvM*uv[0],glm::vec3(posNormM*normal), //left
		glm::vec3(posNormM*pos[3]), uvM*uv[3],glm::vec3(posNormM*normal), //left
		glm::vec3(posNormM*pos[2]), uvM*uv[2],glm::vec3(posNormM*normal), //left
	};


	// Create a vertex array
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(vec3),
		(void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(vec3),
		(void*)(sizeof(vec3) * 2)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindVertexArray(0);

	return vertexArrayObject;
}

void RubikCube::update(float dt)
{
	if (currentMove.valid)
	{
		currentMove.moveTime += dt;
		if (currentMove.moveTime>moveTime)
		{
			currentMove.moveTime = moveTime;
			currentMove.valid = false;
		}
		for (auto c: currentMove.moveCubes)
		{
			c->rotation = rotate(mat4(1), currentMove.moveTime/ moveTime*pi<float>()*0.5f,currentMove.rotateAxis) * c->originalRotation;
		}
	}
}

void RubikCube::makeMove(Move move, bool cw)
{
	if (currentMove.valid)
	{
		return;
	}

	float dir = cw ? 1 : -1;
	switch (move)
	{
	case RubikCube::_None:
		return;
		break;
	case RubikCube::L:
		currentMove.moveCubes = findCubesOfLayer([](vec3 p)->bool {return abs(p.x - (-1)) < 0.5; });
		currentMove.rotateAxis = vec3(1 * dir, 0, 0);
		break;
	case RubikCube::R:
		currentMove.moveCubes = findCubesOfLayer([](vec3 p)->bool {return abs(p.x - (1)) < 0.5; });
		currentMove.rotateAxis = vec3(-1 * dir, 0, 0);
		break;
	case RubikCube::U:
		currentMove.moveCubes = findCubesOfLayer([](vec3 p)->bool {return abs(p.y - (1)) < 0.5; });
		currentMove.rotateAxis = vec3(0, -1 * dir, 0);
		break;
	case RubikCube::D:
		currentMove.moveCubes = findCubesOfLayer([](vec3 p)->bool {return abs(p.y - (-1)) < 0.5; });
		currentMove.rotateAxis = vec3(0, 1 * dir, 0);
		break;
	case RubikCube::F:
		currentMove.moveCubes = findCubesOfLayer([](vec3 p)->bool {return abs(p.z - (1)) < 0.5; });
		currentMove.rotateAxis = vec3(0, 0, -1 * dir);
		break;
	case RubikCube::B:
		currentMove.moveCubes = findCubesOfLayer([](vec3 p)->bool {return abs(p.z - (-1)) < 0.5; });
		currentMove.rotateAxis = vec3(0, 0, 1 * dir);
		break;
	default:
		break;
	}

	for (auto c:currentMove.moveCubes)
	{
		c->originalRotation = c->rotation;
	}
	currentMove.moveTime = 0;
	currentMove.valid = true;
}

void RubikCube::reset()
{
	currentMove.valid = false;
	for (auto c : cubes)
	{
		c->rotation = c->originalRotation = mat4(1);
	}
}

void RubikCube::initialize()
{
	model = mat4(1);
	auto cubeVAO = createCubeVAO();
	for (int y = 0; y < 3; y++)
	{
		for (int z = 0; z < 3; z++)
		{
			for (int x = 0; x < 3; x++)
			{
				auto cube= new Cube();
				cube->vao = cubeVAO;
				cube->translation = translate(mat4(1), vec3(x - 1, y - 1, z - 1));
				cube->rotation = mat4(1);
				if (x == 0)
				{
					Face face;
					face.faceDir = _X;
					face.vao = createFaceVAO(face.faceDir, y, z);
					cube->faces.push_back(face);
				}
				if (x == 2)
				{
					Face face;
					face.faceDir = X;
					face.vao = createFaceVAO(face.faceDir, 2-y, z);
					cube->faces.push_back(face);
				}

				if (y == 0)
				{
					Face face;
					face.faceDir = _Y;
					face.vao = createFaceVAO(face.faceDir, 2-x, z);
					cube->faces.push_back(face);
				}
				if (y == 2)
				{
					Face face;
					face.faceDir = Y;
					face.vao = createFaceVAO(face.faceDir, x, z);
					cube->faces.push_back(face);
				}

				if (z == 0)
				{
					Face face;
					face.faceDir = _Z;
					face.vao = createFaceVAO(face.faceDir, x, y);
					cube->faces.push_back(face);
				}
				if (z == 2)
				{
					Face face;
					face.faceDir = Z;
					face.vao = createFaceVAO(face.faceDir, x, 2-y);
					cube->faces.push_back(face);
				}

				cubes.push_back(cube);
			}
		}
	}
}

void RubikCube::render(GLuint shader, glm::mat4 worldMatrix)
{
	int texLoc = glGetUniformLocation(shader, "tex");
	int MLoc = glGetUniformLocation(shader, "worldMatrix");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,cubeTexture);
	glUniform1i(texLoc, 0);


	for (auto c:cubes)
	{
		auto &cube = *c;
		mat4 m = worldMatrix *model*cube.rotation*cube.translation;
		glUniformMatrix4fv(MLoc, 1, GL_FALSE, &m[0][0]);
		glBindVertexArray(cube.vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	for (auto c : cubes)
	{
		auto &cube = *c;
		mat4 m = worldMatrix *model*cube.rotation*cube.translation;
		for (auto &face:cube.faces)
		{
			glBindTexture(GL_TEXTURE_2D, faceTextures[face.faceDir]);
			glUniformMatrix4fv(MLoc, 1, GL_FALSE, &m[0][0]);
			glBindVertexArray(face.vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	}
}

void RubikCube::setFaceTexture(std::vector<GLuint> faceTex)
{
	faceTextures = faceTex;
}

void RubikCube::setCubeTexture(GLuint cubeTex)
{
	cubeTexture = cubeTex;
}
