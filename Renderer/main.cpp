#include<stdio.h>
#include <GL/glew.h>
#include "Core/Window.h"
#include "Core/Shader.h"
#include "Core/VertexBuffer.h"

#include <iostream>

int main()
{
	
    Window window = {800,600,"Window"};
	glewInit(); // Use GLEW to load modern OpenGL functions from the GPU driver, this must be done after creating the window.
	std::vector<Vertex> vertices = {
		glm::vec3({-0.5f, -0.5f, 0.0f}),
		glm::vec3({0.5f, -0.5f, 0.0f}),
		glm::vec3({0.0f,  0.5f, 0.0f})
	};
	
	VertexBuffer<Vertex> vbo(vertices);
	
	Shader vs = {"./Resources/Shaders/base_vert.glsl", ShaderType::Vertex};
	Shader fs = {"./Resources/Shaders/base_frag.glsl", ShaderType::Fragment};
	GPUProgram shader = {vs, fs};
	
    while(window.IsOpen())
    {
		shader.Bind();
		vbo.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		window.Update();
    }
    
    return 0;
}
