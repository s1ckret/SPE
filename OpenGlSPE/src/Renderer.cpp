#include "Renderer.h"
#include <iostream>

void GLClearErrors() 
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char * function, const char * file, int line) 
{
	while (GLenum error = glGetError()) 
	{
		std::cout << "[OpenGL Error] #" << error << " in " << function << "\nLine: " << line << "\n" << file << "\n";
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_LINE_LOOP, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
