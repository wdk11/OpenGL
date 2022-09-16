#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;//分配的每种类型的对象，标定特定的缓冲区或者我创建的特定对象
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();//析构函数

	void Bind() const;
	void Unbind() const;
};