#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);//�������������0ʱ��һֱִ��
}

bool GLLogCall(const char* function, const char* file, int line)
{//�д���ͷ���һ��������û���󷵻ص���0��ô�Ͳ���ִ��while
	while (GLenum error = glGetError())//Ҳ����˵glGetError����ֵ�ͻ�һֱ���У�ֱ��������ֵ
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}