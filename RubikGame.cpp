#include "RubikGame.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void RubikGame::Initialize(GLFWwindow* window)
{
	m_cubieRenderer.Initialize();
	m_cubeModel.CreateCube();
	m_inputSystem.SetWindow(window);
	m_inputSystem.ObserveKey(GLFW_KEY_SPACE);
	m_inputSystem.ObserveKey(GLFW_KEY_RIGHT);
	m_inputSystem.ObserveKey(GLFW_KEY_LEFT);
	m_inputSystem.ObserveKey(GLFW_KEY_UP);
	m_inputSystem.ObserveKey(GLFW_KEY_DOWN);
	m_turningAngle = 0.0f;
}

void RubikGame::Render(float aspectRatio)
{
	glm::mat4 globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) *
		glm::lookAt(glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::mat4_cast(m_orientationQuaternion);

	float offset = m_cubieRenderer.GetCubieExtension();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				glm::mat4 compound = glm::rotate(globalTransformation, glm::radians(45.0f) * (i % 2), glm::vec3(1.0f, 0.0f, 0.0f)); //rotation has to come first to be around the global axes
				compound = glm::translate(compound, glm::vec3((i - 1) * offset, (j - 1) * offset, (k - 1) * offset)); //moves the cubies to the right position at the start
				//compound = glm::rotate(compound, glm::radians(90.0f) * (i % 2), glm::vec3(1.0f, 0.0f, 0.0f)); //rotiert slice 1 (der einzige bei dem modulo 2 nicht 0 ist) ( 90 grad um die x-achse gegen den uhrzeigersinn
				//compound = glm::rotate(compound, glm::radians(90.0f) * (j % 2), glm::vec3(0.0f, 1.0f, 0.0f));
				//compound = glm::rotate(compound, glm::radians(90.0f) * (k % 2), glm::vec3(0.0f, 0.0f, 1.0f));
				//glm::quat quatRot = glm::angleAxis(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				//glm::mat4 matRot = glm::mat4_cast(quatRot);

				//compound = compound * matRot;	
/*
				if (i == 2) //sollte letzten slice der x-achse auswahlen
				{
					compound = glm::translate(compound, glm::vec3(2.0f, 2.0f, 2.0f));
					compound = glm::rotate(compound, glm::radians(45.0f), glm::vec3(1.f, 0.f, 0.f)); //rotiert um eigene achse der cubies


				}*/

				m_cubieRenderer.Render(compound);
			}
	
}

void RubikGame::ClearResources()
{
	m_cubieRenderer.ClearResources();
}

void RubikGame::Update(double deltaTime)
{
	m_inputSystem.Update();
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_SPACE))
		m_orientationQuaternion = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	float xVel = 0.0f;
	if (m_inputSystem.IsKeyDown(GLFW_KEY_UP))
		xVel = glm::radians(90.0f);
	if (m_inputSystem.IsKeyDown(GLFW_KEY_DOWN))
		xVel = glm::radians(-90.0f);

	float yVel = 0.0f;
	if (m_inputSystem.IsKeyDown(GLFW_KEY_RIGHT))
		yVel = glm::radians(90.0f);
	if (m_inputSystem.IsKeyDown(GLFW_KEY_LEFT))
		yVel = glm::radians(-90.0f);

	glm::quat velocityQuaternion = glm::quat(0.0f, glm::vec3(xVel, yVel, 0.0f));

	m_orientationQuaternion += 0.5f * (float)deltaTime * velocityQuaternion * m_orientationQuaternion;
	m_orientationQuaternion = normalize(m_orientationQuaternion);
}
