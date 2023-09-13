#pragma once
#include <Shader.h>
#include <Renderer.h>

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw(const Renderer& renderer, Shader& shader) const = 0;
};