#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <GL/glew.h>


class VertexBuffer
{
private:
	GLuint id;
	int components;
	std::vector <GLfloat> data;
	bool dirty;
public:
	VertexBuffer();
	~VertexBuffer();

	void add(glm::vec3 value);
	void add(glm::vec4 value);
	void add(glm::vec2 value);
	
	GLuint GetId();
	int GetComponents();
	int GetDataSize();
};

