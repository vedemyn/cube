#pragma once

#include "KeyboardObserver.h"
#include <map>
#include <glm/mat4x4.hpp>

class InputSystem
{
public:
	InputSystem() { m_window = nullptr; }
	void SetWindow(GLFWwindow* window) { m_window = window; }
	void Update();
	void ObserveKey(int key);

	bool IsKeyDown(int key) { return m_keyMapper[key].m_isDown; }
	bool WasKeyPressed(int key) { return m_keyMapper[key].m_wasPressed; }
	bool WasKeyReleased(int key) { return m_keyMapper[key].m_wasReleased; }

	bool IsLeftMouseButtonDown();
	bool IsRightMouseButtonDown();
	bool WasLeftMouseButtonPressed();
	bool WasRightMouseButtonPressed();
	bool WasLeftMouseButtonReleased();
	bool WasRightMouseButtonReleased();

	void GetPickingRay(const glm::mat4& transformationMatrix, glm::vec3& startingPoint, glm::vec3& direction);
	void GetMousePosition(double& xpos, double& ypos);

	float GetDeltaMouseX();
	float GetDeltaMouseY();

private:
	std::map<int, KeyboardObserver> m_keyMapper;
	GLFWwindow* m_window;
	double m_mouseX = 0.0, m_mouseY = 0.0;
	double m_previousMouseX = 0.0, m_previousMouseY = 0.0;
	double m_deltaMouseX = 0.0, m_deltaMouseY = 0.0;
	bool m_LMBDown = false;
	bool m_previousLMBDown = false;
	bool m_RMBDown = false;
	bool m_previousRMBDown = false;
};

