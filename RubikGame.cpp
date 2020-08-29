#include "RubikGame.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <Windows.h>

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
	m_inputSystem.ObserveKey(GLFW_KEY_R);
	m_currentlyRotatedSlice = -1;
	m_rotating = false;
	m_finishRotatingAfterRelease = false;
	m_freezeAutomaticRotation = false;
	m_animationRotationAngle = 0.0f;
	m_animationSpeed = 120.0f;
	m_globalTransformation = glm::mat4(1.0f);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				auto currentCubie = m_cubeModel.getCubie(2 - i, j, 2 - k);
				m_cubeColors[i][j][k][0] = currentCubie.FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f));
				m_cubeColors[i][j][k][1] = currentCubie.FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f));
				m_cubeColors[i][j][k][2] = currentCubie.FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f));
				m_cubeColors[i][j][k][3] = currentCubie.FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f));
				m_cubeColors[i][j][k][4] = currentCubie.FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f));
				m_cubeColors[i][j][k][5] = currentCubie.FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f));

			}
}

void RubikGame::Render(float aspectRatio)
{
	m_globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) * //projection matrix
		glm::lookAt(glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * //view matrix
		glm::mat4_cast(m_orientationQuaternion);

	float offset = m_cubieRenderer.GetCubieExtension();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{

				glm::mat4 compound = m_globalTransformation;
				//animation bit
				if (m_rotating && m_currentlyRotatedSlice >= 0)
				{
					int axis = (m_currentlyRotatedSlice / 3) == 0 ? i : (m_currentlyRotatedSlice / 3) == 1 ? j : k;
					glm::vec3 axisVector = (m_currentlyRotatedSlice / 3) == 0 ? glm::vec3(1.0f, 0.0f, 0.0f) : (m_currentlyRotatedSlice / 3) == 1 ? glm::vec3(0.0f, -1.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 1.0f);

					if (axis == m_currentlyRotatedSlice % 3)
					{
						compound = glm::rotate(compound, glm::radians(m_animationRotationAngle), axisVector);
					}
				}

				compound = glm::translate(compound, glm::vec3((i - 1) * (offset), (j - 1) * (offset), (k - 1) * (offset))); //moves the cubies to the right position

				Cubie currentCubie = m_cubeModel.getCubie(2 - i, j, 2 - k);

				if (!m_rotating)
				{
					m_cubeColors[i][j][k][0] = currentCubie.FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f));
					m_cubeColors[i][j][k][1] = currentCubie.FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f));
					m_cubeColors[i][j][k][2] = currentCubie.FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f));
					m_cubeColors[i][j][k][3] = currentCubie.FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f));
					m_cubeColors[i][j][k][4] = currentCubie.FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f));
					m_cubeColors[i][j][k][5] = currentCubie.FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f));
				}

				m_cubieRenderer.SetColors(m_cubeColors[i][j][k][0], m_cubeColors[i][j][k][1], m_cubeColors[i][j][k][2], m_cubeColors[i][j][k][3], m_cubeColors[i][j][k][4], m_cubeColors[i][j][k][5]);
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
	{
		m_cubeModel.CreateCube();
		m_orientationQuaternion = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	}

	if (m_inputSystem.WasKeyPressed(GLFW_KEY_1))
		RotateSlice(Axis::X_AXIS, 2, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_2))
		RotateSlice(Axis::X_AXIS, 1, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_3))
		RotateSlice(Axis::X_AXIS, 0, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_4))
		RotateSlice(Axis::Y_AXIS, 0, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_5))
		RotateSlice(Axis::Y_AXIS, 1, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_6))
		RotateSlice(Axis::Y_AXIS, 2, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_7))
		RotateSlice(Axis::Z_AXIS, 0, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_8))
		RotateSlice(Axis::Z_AXIS, 1, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_9))
		RotateSlice(Axis::Z_AXIS, 2, true, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F1))
		RotateSlice(Axis::X_AXIS, 2, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F2))
		RotateSlice(Axis::X_AXIS, 1, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F3))
		RotateSlice(Axis::X_AXIS, 0, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F4))
		RotateSlice(Axis::Y_AXIS, 0, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F5))
		RotateSlice(Axis::Y_AXIS, 1, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F6))
		RotateSlice(Axis::Y_AXIS, 2, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F7))
		RotateSlice(Axis::Z_AXIS, 0, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F8))
		RotateSlice(Axis::Z_AXIS, 1, false, false);
	if (m_inputSystem.WasKeyPressed(GLFW_KEY_F9))
		RotateSlice(Axis::Z_AXIS, 2, false, false);


	if (m_inputSystem.WasKeyPressed(GLFW_KEY_R)) 
	{
		//wurfel scramblen
		for (int i = 0; i < 20; i++)
		{
			int axisNumber = std::rand() / (RAND_MAX/3);
			Axis axis = (axisNumber == 0) ? Axis::X_AXIS : (axisNumber == 1) ? Axis::Y_AXIS : Axis::Z_AXIS;
			int n = std::rand() / (RAND_MAX/3);
			bool direction = std::rand() % 2;	
			m_cubeModel.RotateSlice(axis, n, direction);
		}
	}



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


	if (m_inputSystem.IsRightMouseButtonDown())
	{
		xVel = m_inputSystem.GetDeltaMouseY();
		yVel = -m_inputSystem.GetDeltaMouseX();
	}

	if (m_inputSystem.WasLeftMouseButtonReleased())
	{
		m_initialContactPoint = glm::vec3(0.0f);
		m_contactPlaneNormal = glm::vec3(0.0f);
		m_freezeAutomaticRotation = false;
		m_rotating = false;
		if (m_finishRotatingAfterRelease)
			RotateSlice(m_currentRotationAxis, m_currentlyRotatedSlice, m_clockwise, true);
	}

	if (m_inputSystem.IsLeftMouseButtonDown())
	{
		SendRay();
	}

	glm::quat velocityQuaternion = glm::quat(0.0f, glm::vec3(xVel, yVel, 0.0f));

	m_orientationQuaternion += 0.5f * (float)deltaTime * velocityQuaternion * m_orientationQuaternion;
	m_orientationQuaternion = normalize(m_orientationQuaternion);
	if (!m_freezeAutomaticRotation)
	{
		glm::clamp(m_animationRotationAngle, 0.0f, 360.0f);	
		if (m_rotating)
		{
			m_animationRotationAngle += m_animationSpeed * (float)deltaTime;
		}

		if (std::abs(std::abs(std::fmod(m_animationRotationAngle, 360.0f)) - m_animationEndAngle) < 1.0f)
		{
			m_rotating = false;
			m_animationRotationAngle = m_animationEndAngle;
		}
	}
}

void RubikGame::RotateSlice(Axis axis, int sliceNumber, bool clockwise, bool mouseRotation)
{
	if (!m_rotating)
	{
		PlaySound(TEXT("MovingStones.wav"), NULL, SND_ASYNC);
		m_rotating = true;
		m_clockwise = clockwise;
		m_currentRotationAxis = axis;
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
			if (!mouseRotation)
			{
				if (clockwise)
				{
					m_animationRotationAngle = 360.0f;
				}
				else
				{
					m_animationRotationAngle = 0.0f;
				}

			}
			m_animationEndAngle = m_degreesToRotate;
		}


		// input zum modell anpassen.... weil das gewisse achsen andersrum hat
		int sliceNumber = m_currentlyRotatedSlice % 3;
		if (m_currentRotationAxis == Axis::X_AXIS || m_currentRotationAxis == Axis::Z_AXIS) {
			if (sliceNumber == 0)
				sliceNumber = 2;
			else if (sliceNumber == 2)
				sliceNumber = 0;

			m_clockwise = !m_clockwise;
		}
		m_cubeModel.RotateSlice(m_currentRotationAxis, sliceNumber, m_clockwise);

	}
}

void RubikGame::SendRay()
{
	m_freezeAutomaticRotation = true;
	m_rotating = true;
	m_currentlyRotatedSlice = -1;

	glm::vec3 rayPosition, rayDirection;
	m_inputSystem.GetPickingRay(m_globalTransformation, rayPosition, rayDirection);

	std::vector<glm::vec3> sideNormals;

	sideNormals.push_back(glm::vec3(0.0f, 0.0f, -1.0f)); //front normal
	sideNormals.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); //back normal
	sideNormals.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); //left normal
	sideNormals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f)); //right normal
	sideNormals.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); //up normal
	sideNormals.push_back(glm::vec3(0.0f, -1.0f, 0.0f)); //down normal


	if (m_inputSystem.WasLeftMouseButtonPressed() && ((m_contactPlaneNormal == glm::vec3(0.0f)) && (m_initialContactPoint == glm::vec3(0.0f)))) //just when the mouse is first pressed
	{
		//m_contactPlaneNormal = glm::vec3(0.0f);
		//m_initialContactPoint = glm::vec3(0.0f);
		m_finishRotatingAfterRelease = false;
		for (int i = 0; i < 6; i++)
		{
			if (glm::dot(rayDirection, sideNormals[i]) < 0.0f)
			{
				float alpha;
				glm::vec3 planeOrigin = 1.5f * sideNormals[i];
				glm::intersectRayPlane(rayPosition, normalize(rayDirection), planeOrigin, normalize(sideNormals[i]), alpha);
				glm::vec3 intersectionPoint = rayPosition + alpha * normalize(rayDirection);
				if (i / 2 == 0) //z-axis planes - front and back
				{
					if ((std::abs(intersectionPoint.z) == 1.5f) && (std::abs(intersectionPoint.x) <= 1.5f) && (std::abs(intersectionPoint.y) <= 1.5f))
					{
						m_contactPlaneNormal = sideNormals[i];
						m_initialContactPoint = intersectionPoint;
					}
				}
				else if (i / 2 == 1) // x-axis planes - left and right
				{
					if ((std::abs(intersectionPoint.x) == 1.5f) && (std::abs(intersectionPoint.z) <= 1.5f) && (std::abs(intersectionPoint.y) <= 1.5f))
					{
						m_contactPlaneNormal = sideNormals[i];
						m_initialContactPoint = intersectionPoint;
					}
				}
				else // y-axis planes - top and bottom
				{
					if ((std::abs(intersectionPoint.y) == 1.5f) && (std::abs(intersectionPoint.z) <= 1.5f) && (std::abs(intersectionPoint.x) <= 1.5f))
					{
						m_contactPlaneNormal = sideNormals[i];
						m_initialContactPoint = intersectionPoint;
					}
				}

			}

		}
	}
	else if ((m_contactPlaneNormal != glm::vec3(0.0f)) && (m_initialContactPoint != glm::vec3(0.0f)))
	{
		float alpha;
		glm::vec3 planeOrigin = 1.5f * m_contactPlaneNormal;
		glm::intersectRayPlane(rayPosition, normalize(rayDirection), planeOrigin, normalize(m_contactPlaneNormal), alpha);
		glm::vec3 intersectionPoint = rayPosition + alpha * normalize(rayDirection);
		glm::vec3 movementVector = m_initialContactPoint - intersectionPoint;

		if (glm::distance(m_initialContactPoint, intersectionPoint) > 0.2f)
		{
			if (std::abs(m_contactPlaneNormal.x) > 0.9) {
				//not x-axis
				if (std::abs(movementVector.y) > std::abs(movementVector.z))
				{
					m_currentRotationAxis = Axis::Z_AXIS;
					m_clockwise = ((movementVector.y < 0.0f) == (m_contactPlaneNormal.x < 0.0f)); //flipped weil modellachse weird ist, selber schuld - meine achsen sind generell komisch
					m_currentlyRotatedSlice = (m_initialContactPoint.z < -0.5f) ? 6 : (m_initialContactPoint.z > 0.5f) ? 8 : 7;
				}
				else
				{
					m_currentRotationAxis = Axis::Y_AXIS;
					m_clockwise = ((movementVector.z < 0.0f) == (m_contactPlaneNormal.x < 0.0f));
					m_currentlyRotatedSlice = (m_initialContactPoint.y < -0.5f) ? 3 : (m_initialContactPoint.y > 0.5f) ? 5 : 4;
				}
			}
			if (std::abs(m_contactPlaneNormal.y) > 0.9) {
				//not y-axis
				if (std::abs(movementVector.x) > std::abs(movementVector.z))
				{
					m_currentRotationAxis = Axis::Z_AXIS;
					m_clockwise = ((movementVector.x > 0.0f) == (m_contactPlaneNormal.y < 0.0f));
					m_currentlyRotatedSlice = (m_initialContactPoint.z < -0.5f) ? 6 : (m_initialContactPoint.z > 0.5f) ? 8 : 7;
				}
				else
				{
					m_currentRotationAxis = Axis::X_AXIS;
					m_clockwise = ((movementVector.z < 0.0f) == (m_contactPlaneNormal.y < 0.0f));
					m_currentlyRotatedSlice = (m_initialContactPoint.x < -0.5f) ? 0 : (m_initialContactPoint.x > 0.5f) ? 2 : 1;
				}
			}
			if (std::abs(m_contactPlaneNormal.z) > 0.9) {
				//not z-axis
				if (std::abs(movementVector.x) > std::abs(movementVector.y))
				{
					m_currentRotationAxis = Axis::Y_AXIS;
					m_clockwise = ((movementVector.x > 0.0f) == (m_contactPlaneNormal.z < 0.0f));
					m_currentlyRotatedSlice = (m_initialContactPoint.y < -0.5f) ? 3 : (m_initialContactPoint.y > 0.5f) ? 5 : 4;
				}
				else
				{
					m_currentRotationAxis = Axis::X_AXIS;
					m_clockwise = ((movementVector.y > 0.0f) == (m_contactPlaneNormal.z < 0.0f));
					m_currentlyRotatedSlice = (m_initialContactPoint.x < -0.5f) ? 0 : (m_initialContactPoint.x > 0.5f) ? 2 : 1;
				}
			}
		}

		m_finishRotatingAfterRelease = (glm::distance(m_initialContactPoint, intersectionPoint) > 0.5f);

		if (m_clockwise)
		{
			m_animationRotationAngle = glm::clamp(360.0f - glm::distance(m_initialContactPoint, intersectionPoint) * 30.0f, 270.0f, 360.0f);
		}
		else
		{
			m_animationRotationAngle = glm::clamp(glm::distance(m_initialContactPoint, intersectionPoint) * 30.0f, 0.0f, 90.0f);
		}

	}
}
