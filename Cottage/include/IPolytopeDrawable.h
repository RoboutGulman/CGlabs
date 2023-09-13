#pragma once
#include <stdafx.h>

class IPolytopeDrawable
{
public:
	virtual ~IPolytopeDrawable() = default;

	virtual void Draw(const Renderer& renderer, Shader& shader) const = 0;

	virtual glm::mat4 BuildModelMatrix() const = 0;
};