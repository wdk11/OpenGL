#pragma once
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;//��vector����������һ������ȫ��VertexBufferElement�ĵط�
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {}//ÿ�ζ���ʼ��Ϊ0

	//~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);//��̬���Ժ���
	}

	template<>
	void Push<float>(unsigned int count)//ƫ�ػ�
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });//����һ�Σ�����һ������
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)//ƫ�ػ�
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });//����һ�Σ�����һ������
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)//��Ϊʱ�ַ�������������Ҫ��һ��
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });//����һ�Σ�����һ������
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	inline const std::vector<VertexBufferElement> Get_Elements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};