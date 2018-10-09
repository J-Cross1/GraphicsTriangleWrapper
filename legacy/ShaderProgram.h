#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>

class VertexArray;

class ShaderProgram
{
private:
	GLuint id;

public:
	std::string vertShader;
	std::string fragShader;

	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag);

	void draw(VertexArray *vertexArray);

	void SetUniform(std::string uniform, glm::vec4 value);
	void SetUniform(std::string uniform, float value);

	GLuint getId();




	~ShaderProgram();
};

