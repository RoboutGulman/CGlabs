#pragma once
#include "stdafx.h"

#include "Renderer.h"
#include "stb_image/stb_image.h"
#include <iostream>
#include <string>
#include <vector>
class CubemapTexture
{
public:
	CubemapTexture(const std::vector<std::string>& faces)
	{
		GLCall(glGenTextures(1, &m_id));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));

		int width, height;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			stbi_set_flip_vertically_on_load(1);
			auto data = stbi_load(faces[i].c_str(), &width, &height, 0, 3); // 4-RGBA channel
			if (data)
			{
				GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			}

			stbi_image_free(data);
		}

		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	}

	void Bind(GLenum activeTexture = GL_TEXTURE0) const
	{
		GLCall(glActiveTexture(activeTexture));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));
	}
	static void Unbind()
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

private:
	GLuint m_id;
};
