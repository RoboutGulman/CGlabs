#pragma once
#include "stdafx.h"
#include <iomanip>

// m_controls в конструкторе
class Controls
{
public:
	Controls()
		: m_lastTime(0)
		, m_projection(glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f))
		, m_view()
		, m_model(glm::mat4(1.0f))
		, m_position(START_POSITION)
		, m_horizontalAngle(START_HORIZONTAL_ANGLE)
		, m_verticalAngle(START_VERTICAL_ANGLE)
	{
	}

	glm::mat4 GetMVPMatrix(GLFWwindow* window, int width, int height)
	{
		ComputeMatricesFromInputs(window, width, height);
		return m_projection * m_view * m_model;
	}

private:
	const float SPEED = 3.0f;
	const float MOUSE_SPEED = 0.03f;
	const float FOV = 45.0f;
	const glm::vec3 START_POSITION{ 7, 5, -1 };
	const float START_VERTICAL_ANGLE = 106.0f;
	const float START_HORIZONTAL_ANGLE = -14.0f;

	double m_lastTime;
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_model;
	glm::vec3 m_position;
	float m_horizontalAngle;
	float m_verticalAngle;
	bool isMouseCaptureActive = true;

	void ComputeMatricesFromInputs(GLFWwindow* window, int width, float height)
	{
		if (!isMouseCaptureActive)
		{
			return;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isMouseCaptureActive = false;
			return;
		}
		if (m_lastTime == 0)
		{
			glfwSetCursorPos(window, width / 2, height / 2);
			m_lastTime = glfwGetTime();
		}

		auto deltaTime = GetDeltaTime();

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		glfwSetCursorPos(window, width / 2, height / 2);

		std::cout  << "position " << m_position.x << ' ' << m_position.y << ' ' << m_position.z << std::endl;
		//std::cout << "angle " << m_verticalAngle << ' ' << ' ' << m_horizontalAngle << std::endl;

		m_horizontalAngle += MOUSE_SPEED * deltaTime * float(width / 2 - xpos);
		m_verticalAngle += MOUSE_SPEED * deltaTime * float(height / 2 - ypos);

		glm::vec3 viewDirection(
			cos(m_verticalAngle) * sin(m_horizontalAngle),
			sin(m_verticalAngle),
			cos(m_verticalAngle) * cos(m_horizontalAngle));

		glm::vec3 right = glm::vec3(
			sin(m_horizontalAngle - M_PI / 2.0f),
			0,
			cos(m_horizontalAngle - M_PI / 2.0f));

		glm::vec3 up = glm::cross(right, viewDirection);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_position += viewDirection * deltaTime * SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_position -= viewDirection * deltaTime * SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_position += right * deltaTime * SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_position -= right * deltaTime * SPEED;
		}

		m_view = glm::lookAt(
			m_position,
			m_position + viewDirection,
			up);
	}

	float GetDeltaTime()
	{
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - m_lastTime);
		m_lastTime = currentTime;
		return deltaTime;
	}
};
