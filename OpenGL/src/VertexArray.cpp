#include "VertexArray.h"
#include "Renderer.h"//这里包含了Opengl以及GLCall的命令
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));//创建一个顶点数组的缓冲区
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.Get_Elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, 
			element.normalized, layout.GetStride(), (const void*)offset));//常量空指针
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);//相乘的意思
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));//绑定一个顶点数组的缓冲区
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
