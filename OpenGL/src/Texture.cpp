#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	:m_RenderID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Height(0), m_Width(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);//实际上是垂直反转我们的图片，OpenGL希望我们的纹理像素从左下角开始，所以左下角的坐标就是（0,0）
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);//RGBA代表4个通道

	GLCall(glGenTextures(1,&m_RenderID));
	GLCall(glBindTexture(GL_TEXTURE_2D,m_RenderID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//线性重新采样
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//WRAP_S就是水平环绕，所以
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	//绑定数据至GPU
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RenderID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));//指定插
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
