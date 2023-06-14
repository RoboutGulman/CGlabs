#pragma once
#include <Primitives/BasePrimitive.h>
#include <Primitives/BezierCurve.h>
#include <Primitives/Ellipse.h>
#include <Renderer.h>

class Butterfly : public BasePrimitive
{
public:
	Butterfly(glm::vec3 position, float width, float height, glm::vec4 color, float angle = 0.f)
		: BasePrimitive(width, height, position, angle)
		, m_bezier(color)
	{
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		ApplyModelTransform(shader);

		DrawButterflyBody(renderer, shader);
		DrawButterflyWings(renderer, shader);
		DrawButterflyAntenna(renderer, shader);

		SetWidth(-GetWidth());
		ApplyModelTransform(shader);

		DrawButterflyBody(renderer, shader);
		DrawButterflyWings(renderer, shader);
		DrawButterflyAntenna(renderer, shader);

		DisableModelTransform(shader);
		SetWidth(-GetWidth());
	}

private:
	void DrawButterflyBody(const Renderer& renderer, Shader& shader) const
	{
		m_bezier.Draw(renderer, shader, { { 0.f, 0.3f }, { 0.125f, 0.3f }, { 0.0725f, 0.15f }, { 0.f, 0.1f } });

		m_bezier.Draw(renderer, shader, { { 0.f, 0.2f }, { 0.1f, 0.3f }, { 0.025f, 0.55f }, { 0.f, 0.5f } });
	}

	void DrawButterflyWings(const Renderer& renderer, Shader& shader) const
	{
		m_bezier.Draw(renderer, shader, { { 0.f, 0.2f }, { 0.8f, 0.9f }, { 1.5f, .0f }, { 0.f, -0.4f } });

		m_bezier.Draw(renderer, shader, { { 0.f, 0.f }, { 1.0f, -0.4f }, { 0.2f, -1.4f }, { 0.f, -0.4f } });
	}

	void DrawButterflyAntenna(const Renderer& renderer, Shader& shader) const
	{
		m_bezier.Draw(renderer, shader, { { 0.0f, 0.5f }, { 0.3f, 1.2f }, { 0.5f, 1.7f }, { 0.4f, 1.2f } });
	}

private:
	BezierCurve m_bezier;
};
