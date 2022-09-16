#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;//�����ÿ�����͵Ķ��󣬱궨�ض��Ļ����������Ҵ������ض�����
	unsigned int m_Count;//ʵ�����ж��ٸ�����,����һ��������Ӧ����6������
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();//��������

	void Bind() const;
	void Unbind() const;//const�����þ��Ƿ�ֹ�����ڲ����ı�
	inline unsigned int GetCount() const { return m_Count; }//�������������ض��ٸ�����
};