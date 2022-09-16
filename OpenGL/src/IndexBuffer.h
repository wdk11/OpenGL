#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;//分配的每种类型的对象，标定特定的缓冲区或者我创建的特定对象
	unsigned int m_Count;//实际上有多少个索引,比如一个正方形应该有6个索引
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();//析构函数

	void Bind() const;
	void Unbind() const;//const的作用就是防止函数内部被改变
	inline unsigned int GetCount() const { return m_Count; }//内联函数，返回多少个索引
};