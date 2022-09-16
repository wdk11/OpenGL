#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)//初始化m_Count
{
    glGenBuffers(1, &m_RendererID);//1表示一个BUFFER，buffer是一个id,也就是1个id代表一个缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);//将ibo与一个glArrayElementBuffer绑定，数组绑定
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));//绑定进GL_ARRAY_BUFFER后删除缓冲区
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
