#include "../include/stdafx.h"

#include "../include/Texture.h"
#include "stb_image/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path, GLenum target)
	: m_id(0)
	, m_filePath(path)
	, m_localBuffer(nullptr)
	, m_width(0)
	, m_height(0)
	, m_BPP(0)
	, m_target(target)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4); // 4-RGBA channel

	GLCall(glGenTextures(1, &m_id));
	GLCall(glBindTexture(target, m_id));

	GLCall(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (!m_localBuffer)
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}

	if (target == GL_TEXTURE_2D)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
		stbi_image_free(m_localBuffer);
		return;
	}
	if (target == GL_TEXTURE_1D)
	{
		GLCall(glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, m_width, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_1D, m_id));
		stbi_image_free(m_localBuffer);
		return;
	}
	std::cout << "Invalid target value\n";
	/* GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // S - x for texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // T - y for texture

	if (m_localBuffer)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
		stbi_image_free(m_localBuffer);
	}
	else
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}*/
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_id));
}

void Texture::Bind(GLenum activeTexture) const
{
	GLCall(glActiveTexture(activeTexture));
	GLCall(glBindTexture(m_target, m_id));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(m_target, 0));
}
