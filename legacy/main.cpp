#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <exception>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/*
const GLfloat positions[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

const GLfloat colors[] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f
};
*/


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

//	GLuint vaoId = 0;

//	// Create a new VAO on the GPU and bind it
//	glGenVertexArrays(1, &vaoId);
//	if (!vaoId)
//	{
//		throw std::exception();
//	}
//	glBindVertexArray(vaoId);

	/*
	GLuint positionsVboId = 0;
	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &positionsVboId);
	if (!positionsVboId)
	{
		throw std::exception();
	}
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/

	VertexBuffer *positions = new VertexBuffer();
	positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
	positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
	positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used

//	glBindBuffer(GL_ARRAY_BUFFER, positions->GetId());
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
//		3 * sizeof(GLfloat), (void *)0);
//	glEnableVertexAttribArray(0);

	VertexBuffer *colors = new VertexBuffer();
	colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	VertexArray *shape = new VertexArray();
	shape->SetBuffer("in_Position", positions);
	shape->SetBuffer("in_Color", colors);

	// Bind the color VBO, assign it to position 1 on the bound VAO
	// and flag it to be used
//	glBindBuffer(GL_ARRAY_BUFFER, colors->GetId());
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
//		4 * sizeof(GLfloat), (void *)0);
//	glEnableVertexAttribArray(1);

//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
	
	/*const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;             " \
		"                                        " \
		"void main()                             " \
		"{                                       " \
		"  gl_Position = vec4(in_Position, 1.0); " \
		"}                                       ";*/

	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;			" \
		"attribute vec4 in_Color;				" \
		"										" \
		"varying vec4 ex_Color;					" \
		"							" \
		"void main()				" \
		"{							" \
		"  gl_Position = vec4(in_Position, 1.0);" \
		"  ex_Color = in_Color;		" \
		"}							" \
		"							";

	
	
	/*
	GLuint colorsVboId = 0;
	// Create a colors VBO on the GPU and bind it
	glGenBuffers(1, &colorsVboId);
	if (!colorsVboId)
	{
		throw std::exception();
	}
	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	*/

	// Create a new vertex shader, attach source code, compile it and
	// check for errors.
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	const GLchar *fragmentShaderSrc =
		"varying vec4 ex_Color;" \
		"void main()" \
		"{" \
		"  gl_FragColor = ex_Color;" \
		"}";

	// Create a new fragment shader, attach source code, compile it and
	// check for errors.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}


	// Create new shader program and attach our shader objects
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glBindVertexArray(0);


	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.

	glBindAttribLocation(programId, 0, "in_Position");
	glBindAttribLocation(programId, 1, "in_Color");
	
	
	// Perform the link and check for failure
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}

	//  // Store location of the color uniform and check if successfully found
	//  GLint colorUniformId = glGetUniformLocation(programId, "in_Color");
	//  if (colorUniformId == -1)
	//  {
	//  	throw std::exception();
	//  }
	//  
	//  
	//  
	//  // Bind the shader to change the uniform, set the uniform and reset state
	//  glUseProgram(programId);
	//  glUniform4f(colorUniformId, 0, 1, 0, 1);
	//  glUseProgram(0);


	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
	// Instruct OpenGL to use our shader program and our VAO


	bool quit = false;



	while (!quit)
	{
		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(programId);
			glBindVertexArray(shape->GetId());
			// Draw 3 vertices (a triangle)
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// Reset the state
			glBindVertexArray(0);
			glUseProgram(0);

			SDL_GL_SwapWindow(window);
		}

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}