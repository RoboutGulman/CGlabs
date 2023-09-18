#pragma once
#include "../IDrawable.h"
#include "../IDrawable.h"

#include <memory>

class CompoundObject : public IDrawable
{
public:
	void Draw(const Renderer& renderer, Shader& shader) const override
	{
		for (auto&& roomPart : m_parts)
		{
			roomPart->Draw(renderer, shader);
		}
	}

protected:
	std::vector<std::unique_ptr<IDrawable>> m_parts;
};
