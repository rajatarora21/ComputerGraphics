#pragma once

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>


class shaderloader
{
public:
	shaderloader();
	~shaderloader();
	static GLuint LoadShaders(std::string vertex_shader_path, std::string fragment_shader_path);
	GLuint getProgramId();
private:
	GLuint ShaderProgramId;
};