#pragma once
#include "Renderer.h"

class Texture
{
private:
	unsigned int m_id;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_BPP;
	GLenum m_target;

public:
	Texture(const std::string& path, GLenum target = GL_TEXTURE_2D);
	~Texture();

	void Bind(GLenum activeTexture = GL_TEXTURE0) const;
	void Unbind() const;

	inline int GetWidth() const
	{
		return m_width;
	};

	inline int GetHeight() const
	{
		return m_height;
	};
};
