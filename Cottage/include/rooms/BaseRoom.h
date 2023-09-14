#pragma once
#include "../IDrawable.h"
#include "../IPolytopeDrawable.h"

class BaseRoom : public IDrawable
{
public:
	void Draw(const Renderer& renderer, Shader& shader) const override
	{
		for (auto&& roomPart : m_roomParts)
		{
			roomPart->Draw(renderer, shader);
		}
	}

protected:
	std::vector<std::unique_ptr<IPolytopeDrawable>> m_roomParts;
};
