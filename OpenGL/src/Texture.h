#pragma once
#include "Renderer.h"
#include <string>

class Texture
{
private:
	unsigned int m_RenderID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;//纹理的本地存储
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;//slot就是你们想要绑定纹理的插槽
	void Unbind() const;

	inline int GetWidth() const
	{
		return m_Width;
	};

	inline int GetHeight() const
	{
		return m_Height;
	};
};