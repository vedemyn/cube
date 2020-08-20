#pragma once
#include "GameInterface.h"
#include "CubieRenderer.h"
#include "InputSystem.h"
#include <glm/vec3.hpp>

class TestMouse : public GameInterface
{
public:
	virtual void Initialize(GLFWwindow* window);
	virtual void Render(float aspectRatio);
	virtual void ClearResources();
	virtual void Update(double deltaTime);

private:
	CubieRenderer m_cubieRenderer;
	InputSystem m_input;
	glm::vec3 m_cubePosition;
	glm::mat4 m_viewProject;
};

