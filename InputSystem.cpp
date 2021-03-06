#include "InputSystem.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


void InputSystem::Update()
{
	for (auto i = m_keyMapper.begin(); i != m_keyMapper.end(); ++i)
		i->second.Update();
	m_previousMouseX = m_mouseX;
	m_previousMouseY = m_mouseY;
	glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
	m_deltaMouseX = m_previousMouseX - m_mouseX;
	m_deltaMouseY = m_previousMouseY - m_mouseY;

	m_previousLMBDown = m_LMBDown;
	m_previousRMBDown = m_RMBDown;
	m_LMBDown = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	m_RMBDown = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

void InputSystem::ObserveKey(int key)
{
	m_keyMapper[key] = KeyboardObserver(m_window, key);
}

bool InputSystem::IsLeftMouseButtonDown()
{
	return m_LMBDown;
}

bool InputSystem::IsRightMouseButtonDown()
{
	return m_RMBDown;
}

bool InputSystem::WasLeftMouseButtonPressed()
{
	return (m_LMBDown && !m_previousLMBDown);
}

bool InputSystem::WasRightMouseButtonPressed()
{
	return (m_RMBDown && !m_previousRMBDown);
}

bool InputSystem::WasLeftMouseButtonReleased()
{
	return (!m_LMBDown && m_previousLMBDown);
}

bool InputSystem::WasRightMouseButtonReleased()
{
	return (!m_RMBDown && m_previousRMBDown);
}

void InputSystem::GetPickingRay(const glm::mat4& transformationMatrix, glm::vec3& startingPoint, glm::vec3& direction)
{
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos); //wo ist der cursor

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight); // wie gross ist das fenster

	xpos = (xpos / screenWidth) * 2.0 - 1.0; //umrechnen in clip space
	ypos = 1.0 - 2.0 * (ypos / screenHeight); //hier andersrum weil achse umgedreht ist

	glm::vec4 nearPoint = glm::vec4((float)xpos, (float)ypos, 0.01f, 1.0f); //wo soll strahl anfangen
	glm::vec4 farPoint = nearPoint; //wo soll strahl enden
	farPoint.z = 0.99f; //nur halt fast am ende des bereiches

	glm::mat4 inverse = glm::inverse(transformationMatrix); 
	nearPoint = inverse * nearPoint;
	farPoint = inverse * farPoint;

	nearPoint /= nearPoint.w; //auf kartesische koordinaten zuruckbringen
	farPoint /= farPoint.w;

	startingPoint = nearPoint;
	direction = farPoint - nearPoint;

	direction = glm::normalize(direction);
}

void InputSystem::GetMousePosition(double& xpos, double& ypos)
{
	glfwGetCursorPos(m_window, &xpos, &ypos);
}

float InputSystem::GetDeltaMouseX()
{
	return  (float)m_deltaMouseX;
}

float InputSystem::GetDeltaMouseY()
{
	return (float)m_deltaMouseY;
}



