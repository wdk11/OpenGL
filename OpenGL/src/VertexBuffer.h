#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;//�����ÿ�����͵Ķ��󣬱궨�ض��Ļ����������Ҵ������ض�����
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();//��������

	void Bind() const;
	void Unbind() const;
};