#include "../include/stdafx.h"

#include "../include/Texture.h"
#include "stb_image/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path)
	: m_rendererID(0)
	, m_filePath(path)
	, m_localBuffer(nullptr)
	, m_width(0)
	, m_height(0)
	, m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4); // 4-RGBA channel

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // S - x for texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // T - y for texture

	if (m_localBuffer)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
		stbi_image_free(m_localBuffer);
	}
	else
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
	GLCall(glBindTextureUnit(slot, m_rendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
