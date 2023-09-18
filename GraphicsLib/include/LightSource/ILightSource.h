#pragma once
#include "../stdafx.h"

#include <memory>

/*
	»нтерфейс "»сточник света"
*/
class ILightSource
{
public:
	virtual ~ILightSource(void) = default;

	/*
		”становка и получение матрицы трансформации источника света
	*/
	virtual void SetTransform(glm::mat4 const& transform) = 0;
	virtual glm::mat4 const& GetTransform() const = 0;

	/*
		”становка и получение интенсивности диффузного света
	*/
	virtual void SetDiffuseIntensity(glm::vec4 const& diffuseIntensity) = 0;
	virtual glm::vec4 const& GetDiffuseIntensity() const = 0;

	/*
		”становка и получение интенсивности фонового света
	*/
	virtual void SetAmbientIntensity(glm::vec4 const& ambientIntensity) = 0;
	virtual glm::vec4 const& GetAmbientIntensity() const = 0;

	/*
		”становка и получение интенсивности отраженного света
	*/
	virtual void SetSpecularIntensity(glm::vec4 const& specularIntensity) = 0;
	virtual glm::vec4 const& GetSpecularIntensity() const = 0;

	/*
		»нтенсивность света, излучаемого в направлении от источника к заданной точке, заданной в мировой системе координат.
		ƒл€ точечных источников позвол€ет задать ослабление света в зависимости от рассто€ни€
		ƒл€ конических источников света попутно позвол€ет задать ослабление излучаемого света в зависимости
		от угла отклонени€ от вектора направлени€
	*/
	virtual double GetIntensityInDirection(glm::vec3 const& direction) const = 0;

	/*
		Ќаправление на источник света из указанной точки, заданной в мировой системе координат
	*/
	virtual glm::vec3 GetDirectionFromPoint(glm::vec3 const& point) const = 0;

	// ѕолучение позиции источника света в мировых координатах
	virtual glm::vec3 const& GetPositionInWorldSpace() const = 0;
};

using ILightSourcePtr = std::shared_ptr<ILightSource>;
