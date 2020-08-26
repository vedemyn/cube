#include "RubikGame.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

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
	m_inputSystem.ObserveKey(GLFW_KEY_1);
	m_inputSystem.ObserveKey(GLFW_KEY_2);
	m_inputSystem.ObserveKey(GLFW_KEY_3);
	m_inputSystem.ObserveKey(GLFW_KEY_4);
	m_inputSystem.ObserveKey(GLFW_KEY_5);
	m_inputSystem.ObserveKey(GLFW_KEY_6);
	m_inputSystem.ObserveKey(GLFW_KEY_7);
	m_inputSystem.ObserveKey(GLFW_KEY_8);
	m_inputSystem.ObserveKey(GLFW_KEY_9);
	m_inputSystem.ObserveKey(GLFW_KEY_F1);
	m_inputSystem.ObserveKey(GLFW_KEY_F2);
	m_inputSystem.ObserveKey(GLFW_KEY_F3);
	m_inputSystem.ObserveKey(GLFW_KEY_F4);
	m_inputSystem.ObserveKey(GLFW_KEY_F5);
	m_inputSystem.ObserveKey(GLFW_KEY_F6);
	m_inputSystem.ObserveKey(GLFW_KEY_F7);
	m_inputSystem.ObserveKey(GLFW_KEY_F8);
	m_inputSystem.ObserveKey(GLFW_KEY_F9);
	m_currentlyRotatedSlice = -1;
	m_rotating = false;
	m_animationRotationAngle = 0.0f;
	m_animationSpeed = 120.0f;
}

void RubikGame::Render(float aspectRatio)
{
	glm::mat4 globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) * //projection matrix
		glm::lookAt(glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * //view matrix
		glm::mat4_cast(m_orientationQuaternion);

	float offset = m_cubieRenderer.GetCubieExtension();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{

				glm::mat4 compound = globalTransformation;
				//animation bit
				if (m_rotating)
				{
					int axis = (m_currentlyRotatedSlice / 3) == 0 ? i : (m_currentlyRotatedSlice / 3) == 1 ? j : k;
					glm::vec3 axisVector = (m_currentlyRotatedSlice / 3) == 0 ? glm::vec3(1.0f, 0.0f, 0.0f) : (m_currentlyRotatedSlice / 3) == 1 ? glm::vec3(0.0f, -1.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 1.0f);

					if (axis == m_currentlyRotatedSlice % 3)
					{
						compound = glm::rotate(compound, glm::radians(m_animationRotationAngle), axisVector);
					}
				}

				compound = glm::translate(compound, glm::vec3((i - 1) * (offset + 0.3f), (j - 1) * (offset + 0.3f), (k - 1) * (offset + 0.3f))); //moves the cubies to the right position
/*
				//actual rotation bit
				glm::quat rot = glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

				//x-axis
				if ((i == 0) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 0) && ((m_currentlyRotatedSlice % 3) == i)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[0]), glm::vec3(1.0f, 0.0f, 0.0f));
				}
				if ((i == 1) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 0) && ((m_currentlyRotatedSlice % 3) == i)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[1]), glm::vec3(1.0f, 0.0f, 0.0f));
				}
				if ((i == 2) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 0) && ((m_currentlyRotatedSlice % 3) == i)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[2]), glm::vec3(1.0f, 0.0f, 0.0f));
				}

				//y-axis
				if ((j == 0) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 1) && ((m_currentlyRotatedSlice % 3) == j)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[3]), glm::vec3(0.0f, -1.0f, 0.0f));
				}
				if ((j == 1) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 1) && ((m_currentlyRotatedSlice % 3) == j)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[4]), glm::vec3(0.0f, -1.0f, 0.0f));
				}
				if ((j == 2) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 1) && ((m_currentlyRotatedSlice % 3) == j)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[5]), glm::vec3(0.0f, -1.0f, 0.0f));
				}

				//z-axis
				if ((k == 0) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 2) && ((m_currentlyRotatedSlice % 3) == k)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[6]), glm::vec3(0.0f, 0.0f, 1.0f));
				}
				if ((k == 1) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 2) && ((m_currentlyRotatedSlice % 3) == k)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[7]), glm::vec3(0.0f, 0.0f, 1.0f));
				}
				if ((k == 2) && !(m_rotating && ((m_currentlyRotatedSlice / 3) == 2) && ((m_currentlyRotatedSlice % 3) == k)))
				{
					rot = rot * glm::angleAxis(glm::radians(m_sliceRotationDegrees[8]), glm::vec3(0.0f, 0.0f, 1.0f));
				}

				glm::mat4 rotmat = glm::mat4_cast(rot);
				if (!(m_rotating && ((m_currentlyRotatedSlice / 3) == 0) && ((m_currentlyRotatedSlice % 3) == i)))
					compound =  compound * rotmat ;

*/
				if (!(m_rotating && ((m_currentlyRotatedSlice / 3) == 2) && ((m_currentlyRotatedSlice % 3) == k)))
				{
					auto currentCubie = m_cubeModel.getCubie(2 - i, j, 2 - k);
					auto left = currentCubie.FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f));
					auto right = currentCubie.FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f));
					auto up = currentCubie.FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f));
					auto down = currentCubie.FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f));
					auto front = currentCubie.FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f));
					auto back = currentCubie.FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f));
					m_cubieRenderer.SetColors(left, right, up, down, front, back);
				}
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
			
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_1))
		RotateSlice(Axis::X_AXIS, 2, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_2))
		RotateSlice(Axis::X_AXIS, 1, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_3))
		RotateSlice(Axis::X_AXIS, 0, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_4))
		RotateSlice(Axis::Y_AXIS, 0, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_5))
		RotateSlice(Axis::Y_AXIS, 1, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_6))
		RotateSlice(Axis::Y_AXIS, 2, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_7))
		RotateSlice(Axis::Z_AXIS, 0, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_8))
		RotateSlice(Axis::Z_AXIS, 1, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_9))
		RotateSlice(Axis::Z_AXIS, 2, true);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F1))
		RotateSlice(Axis::X_AXIS, 2, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F2))
		RotateSlice(Axis::X_AXIS, 1, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F3))
		RotateSlice(Axis::X_AXIS, 0, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F4))
		RotateSlice(Axis::Y_AXIS, 0, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F5))
		RotateSlice(Axis::Y_AXIS, 1, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F6))
		RotateSlice(Axis::Y_AXIS, 2, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F7))
		RotateSlice(Axis::Z_AXIS, 0, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F8))
		RotateSlice(Axis::Z_AXIS, 1, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F9))
		RotateSlice(Axis::Z_AXIS, 2, false);


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
	if (m_rotating)
	{
		m_animationRotationAngle += m_animationSpeed * (float) deltaTime;
	}
	//std::cout << "" << m_animationRotationAngle << ", " << m_animationEndAngle << ", " << std::abs(m_animationRotationAngle - m_animationEndAngle) << std::endl;
	if (std::abs(std::abs(std::fmod(m_animationRotationAngle, 360.0f)) - m_animationEndAngle) < 1.0f ) 
	{
		m_rotating = false;
		m_animationRotationAngle = m_animationEndAngle;
	}

	m_orientationQuaternion += 0.5f * (float)deltaTime * velocityQuaternion * m_orientationQuaternion;
	m_orientationQuaternion = normalize(m_orientationQuaternion);
}

void RubikGame::RotateSlice(Axis axis, int sliceNumber, bool clockwise)
{
	if (!m_rotating)
	{
		m_rotating = true;
		if (axis == Axis::X_AXIS)
		{
			if (sliceNumber == 0)
				m_currentlyRotatedSlice = 0;
			if (sliceNumber == 1)
				m_currentlyRotatedSlice = 1;
			if (sliceNumber == 2)
				m_currentlyRotatedSlice = 2;
		}
		if (axis == Axis::Y_AXIS)
		{
			if (sliceNumber == 0)
				m_currentlyRotatedSlice = 3;
			if (sliceNumber == 1)
				m_currentlyRotatedSlice = 4;
			if (sliceNumber == 2)
				m_currentlyRotatedSlice = 5;
		}
		if (axis == Axis::Z_AXIS)
		{
			if (sliceNumber == 0)
				m_currentlyRotatedSlice = 6;
			if (sliceNumber == 1)
				m_currentlyRotatedSlice = 7;
			if (sliceNumber == 2)
				m_currentlyRotatedSlice = 8;
		}

		if (clockwise) 
		{
			m_degreesToRotate = 270.0f;
			m_animationSpeed = -120.0f;
		}
		else 
		{
			m_degreesToRotate = 90.0f;
			m_animationSpeed = 120.0f;
		}


		if (m_currentlyRotatedSlice > -1)
		{
			if (clockwise)
			{
				if (std::abs(m_sliceRotationDegrees[m_currentlyRotatedSlice]) < 1.0f)
				{
					m_animationRotationAngle = 360.0f;
				}
			}
			else
			{
				m_animationRotationAngle = std::fmod(m_sliceRotationDegrees[m_currentlyRotatedSlice], 360.0f);
			}
			m_animationEndAngle = std::fmod(m_animationRotationAngle + m_degreesToRotate, 360.0f);
			m_sliceRotationDegrees[m_currentlyRotatedSlice] = m_animationEndAngle;
		}



		// input zum modell anpassen.... weil das gewisse achsen andersrum hat
		if (axis == Axis::X_AXIS || axis == Axis::Z_AXIS) {
			if (sliceNumber == 0)
				sliceNumber = 2;
			else if (sliceNumber == 2)
				sliceNumber = 0;

			clockwise = !clockwise;

		}
		m_cubeModel.RotateSlice(axis, sliceNumber, clockwise);
	}
}
