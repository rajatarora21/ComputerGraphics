#include <string>
#include <glm/glm.hpp>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

class TextRenderer
{
protected:
	GLuint vao;
	GLuint vbo;
	std::string text;
	glm::vec2 pos;
	float fontSize=20;
	GLuint fontTex;

	void generateTextMesh();
	void initializeGLResource();
public:
	void setText(const char *s);
	void setPosition(glm::vec2 pos);
	void setFontSize(float size);
	void setFontTexture(GLuint tex);
	void render(GLuint shader);
};