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
	std::vector<VertexBufferElement> m_Elements;//用vector容器创建了一个里面全是VertexBufferElement的地方
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {}//每次都初始化为0

	//~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);//静态断言函数
	}

	template<>
	void Push<float>(unsigned int count)//偏特化
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });//调用一次，插入一批数据
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)//偏特化
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });//调用一次，插入一批数据
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)//因为时字符串类型所以需要归一化
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });//调用一次，插入一批数据
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	inline const std::vector<VertexBufferElement> Get_Elements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};