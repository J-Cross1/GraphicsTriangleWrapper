#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(std::string vert, std::string frag)
{
}


void SetUniform(std::string uniform, glm::vec4 value)
{}
void SetUniform(std::string uniform, float value)
{}


GLuint ShaderProgram::getId()
{
	return 0;
}

ShaderProgram::~ShaderProgram()
{
}
