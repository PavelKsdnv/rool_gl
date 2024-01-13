#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include "OpenGl_Room.h"

void Create3DObject();
GLuint vao, vbo, ebo;


int main(int argc, char* args[])
{
	// init sdl
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("3D Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// init glew
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK) {
		// Handle initialization error
		std::cerr << "Error initializing GLEW: " << glewGetErrorString(glewInitResult) << std::endl;
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Create3DObject();

	return RenderLoop(window);
}

int RenderLoop(SDL_Window* window)
{
	while (true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set up a transformation matrix (e.g., model, view, and projection matrices)
		// Apply shaders, textures, and other rendering configurations

		// Bind the Vertex Array Object (VAO) that you created earlier
		glBindVertexArray(vao);

		// Draw the cube using the indices buffer
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// Unbind the VAO
		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				// Handle window close event
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
			}
		}
	}

}

void Create3DObject()
{
	// Define vertex and index data for a cube (you may use a more sophisticated model)
	float vertices[] = {
		// Front face
	   -0.5f, -0.5f,  0.5f, // Vertex 0
		0.5f, -0.5f,  0.5f, // Vertex 1
		0.5f,  0.5f,  0.5f, // Vertex 2
	   -0.5f,  0.5f,  0.5f, // Vertex 3

	   // Back face
	  -0.5f, -0.5f, -0.5f, // Vertex 4
	   0.5f, -0.5f, -0.5f, // Vertex 5
	   0.5f,  0.5f, -0.5f, // Vertex 6
	  -0.5f,  0.5f, -0.5f, // Vertex 7

	  // Top face
	  0.5f,  0.5f,  0.5f, // Vertex 2 (repeat from front face)
	 -0.5f,  0.5f,  0.5f, // Vertex 3 (repeat from front face)
	 -0.5f,  0.5f, -0.5f, // Vertex 7 (repeat from back face)
	  0.5f,  0.5f, -0.5f, // Vertex 6 (repeat from back face)

	  // Bottom face
	 -0.5f, -0.5f,  0.5f, // Vertex 0 (repeat from front face)
	  0.5f, -0.5f,  0.5f, // Vertex 1 (repeat from front face)
	  0.5f, -0.5f, -0.5f, // Vertex 5 (repeat from back face)
	 -0.5f, -0.5f, -0.5f, // Vertex 4 (repeat from back face)

	 // Right face
	 0.5f, -0.5f,  0.5f, // Vertex 1 (repeat from front face)
	 0.5f, -0.5f, -0.5f, // Vertex 5 (repeat from back face)
	 0.5f,  0.5f, -0.5f, // Vertex 6 (repeat from back face)
	 0.5f,  0.5f,  0.5f, // Vertex 2 (repeat from front face)

	 // Left face
	-0.5f, -0.5f,  0.5f, // Vertex 0 (repeat from front face)
	-0.5f,  0.5f,  0.5f, // Vertex 3 (repeat from front face)
	-0.5f,  0.5f, -0.5f, // Vertex 7 (repeat from back face)
	-0.5f, -0.5f, -0.5f  // Vertex 4 (repeat from back face)
	};

	unsigned int indices[] = {
		0, 1, 2,  // Front face
		2, 3, 0,

		4, 5, 6,  // Back face
		6, 7, 4,

		8, 9, 10, // Top face
		10, 11, 8,

		12, 13, 14, // Bottom face
		14, 15, 12,

		16, 17, 18, // Right face
		18, 19, 16,

		20, 21, 22, // Left face
		22, 23, 20
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set up vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
