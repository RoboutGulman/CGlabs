#pragma once
#include "../../TexturedPolytope.h"
#include "Cube.h"
#include <memory>

class TextureCube : public TexturedPolytope
{
public:
	TextureCube(std::unique_ptr<Cube>&& polytope, const std::string& texturePath)
		: TexturedPolytope(std::move(polytope), texturePath)
	{
	}
};
