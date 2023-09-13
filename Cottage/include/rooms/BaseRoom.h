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
			//shader.SetUniformMatrix4fv(uniformMap.modelUniform.c_str(), roomPart->BuildModelMatrix())
			//program.SetUniform4fv(uniformMap.modelUniform.c_str(), roomPart->BuildModelMatrix());
			roomPart->Draw(renderer, shader);
		}
	}

protected:
	std::vector<std::unique_ptr<IPolytopeDrawable>> m_roomParts;
};
