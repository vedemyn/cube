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

	void GetPickingRay(const glm::mat4& transformationMatrix, glm::vec3& startingPoint, glm::vec3& direction);
	void GetMousePOsition(double& xpos, double& ypos);
	
private:
	std::map<int, KeyboardObserver> m_keyMapper;
	GLFWwindow* m_window;
};

