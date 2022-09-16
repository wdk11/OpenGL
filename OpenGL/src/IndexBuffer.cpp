#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)//��ʼ��m_Count
{
    glGenBuffers(1, &m_RendererID);//1��ʾһ��BUFFER��buffer��һ��id,Ҳ����1��id����һ��������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);//��ibo��һ��glArrayElementBuffer�󶨣������
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));//�󶨽�GL_ARRAY_BUFFER��ɾ��������
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
