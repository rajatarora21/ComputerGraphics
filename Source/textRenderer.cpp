#include "textRenderer.h"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

void TextRenderer::generateTextMesh()
{
	initializeGLResource();
	vector<vec2> data;

	float x = 0;
	for (auto c:text)
	{
		float col = c % 16;
		float row = c / 16;
		data.push_back({ x - fontSize*0.5f,fontSize*0.5f }); data.push_back({ col / 16,1 - (row / 16) });
		data.push_back({ x - fontSize*0.5f,-fontSize*0.5f }); data.push_back({ col / 16,1 - ((row + 1) / 16) });
		data.push_back({ x + fontSize*0.5,-fontSize*0.5f }); data.push_back({ (col + 1) / 16,1 - ((row + 1) / 16) });
		data.push_back({ x - fontSize*0.5f,fontSize*0.5f }); data.push_back({ col / 16,1 - (row / 16) });
		data.push_back({ x + fontSize*0.5,-fontSize*0.5f }); data.push_back({ (col + 1) / 16,1 - ((row + 1) / 16) });
		data.push_back({ x + fontSize*0.5f,fontSize*0.5f }); data.push_back({ (col+1) / 16,1 - (row  / 16) });
		x += fontSize;
	}

	if (data.size())
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec2)*data.size(), data.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void TextRenderer::initializeGLResource()
{
	if (!vbo)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 512 * 6 * 2 * sizeof(vec2), 0, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vec2), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vec2), (void *)(sizeof(vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void TextRenderer::setText(const char * s)
{
	if (text!=s)
	{
		text = s;
		generateTextMesh();
	}
}

void TextRenderer::setPosition(vec2 pos)
{
	this->pos = pos;
}

void TextRenderer::setFontSize(float size)
{
	if (fontSize != size)
	{
		fontSize = size;
		generateTextMesh();
	}
}

void TextRenderer::setFontTexture(GLuint tex)
{
	fontTex = tex;
}

void TextRenderer::render(GLuint shader)
{
	mat4 model = translate(mat4(1), vec3(pos.x, pos.y, 0));
	int worldmatrixlocation = glGetUniformLocation(shader, "worldMatrix");
	glUniformMatrix4fv(worldmatrixlocation, 1, GL_FALSE, &model[0][0]);
	int texLoc = glGetUniformLocation(shader, "tex");
	glUniform1i(texLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontTex);

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	
	if (text.size())
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);
		glBindVertexArray(0);
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}
