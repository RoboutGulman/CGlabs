#pragma once
#include "../stdafx.h"

#include <memory>

/*
	��������� "�������� �����"
*/
class ILightSource
{
public:
	virtual ~ILightSource(void) = default;

	/*
		��������� � ��������� ������� ������������� ��������� �����
	*/
	virtual void SetTransform(glm::mat4 const& transform) = 0;
	virtual glm::mat4 const& GetTransform() const = 0;

	/*
		��������� � ��������� ������������� ���������� �����
	*/
	virtual void SetDiffuseIntensity(glm::vec4 const& diffuseIntensity) = 0;
	virtual glm::vec4 const& GetDiffuseIntensity() const = 0;

	/*
		��������� � ��������� ������������� �������� �����
	*/
	virtual void SetAmbientIntensity(glm::vec4 const& ambientIntensity) = 0;
	virtual glm::vec4 const& GetAmbientIntensity() const = 0;

	/*
		��������� � ��������� ������������� ����������� �����
	*/
	virtual void SetSpecularIntensity(glm::vec4 const& specularIntensity) = 0;
	virtual glm::vec4 const& GetSpecularIntensity() const = 0;

	/*
		������������� �����, ����������� � ����������� �� ��������� � �������� �����, �������� � ������� ������� ���������.
		��� �������� ���������� ��������� ������ ���������� ����� � ����������� �� ����������
		��� ���������� ���������� ����� ������� ��������� ������ ���������� ����������� ����� � �����������
		�� ���� ���������� �� ������� �����������
	*/
	virtual double GetIntensityInDirection(glm::vec3 const& direction) const = 0;

	/*
		����������� �� �������� ����� �� ��������� �����, �������� � ������� ������� ���������
	*/
	virtual glm::vec3 GetDirectionFromPoint(glm::vec3 const& point) const = 0;

	// ��������� ������� ��������� ����� � ������� �����������
	virtual glm::vec3 const& GetPositionInWorldSpace() const = 0;
};

using ILightSourcePtr = std::shared_ptr<ILightSource>;
