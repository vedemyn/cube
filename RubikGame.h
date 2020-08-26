#pragma once
#include "GameInterface.h"
#include "CubieRenderer.h"
#include "InputSystem.h"
#include "CubeModel.h"
#include <glm/ext/quaternion_float.hpp>

class RubikGame : 
	public GameInterface
{
public:

	virtual void Initialize(GLFWwindow* window);
	virtual void Render(float aspectRatio);
	virtual void ClearResources();
	virtual void Update(double deltaTime);
	void RotateSlice(Axis axis, int sliceNumber, bool clockwise);

private:
	CubieRenderer m_cubieRenderer;
	InputSystem m_inputSystem;
	CubeModel m_cubeModel;
	

	glm::quat m_orientationQuaternion;
	int m_currentlyRotatedSlice;
	float m_degreesToRotate;
	float m_animationRotationAngle;
	float m_animationEndAngle;
	float m_animationSpeed;
	float m_sliceRotationDegrees[9];
	float m_oldSliceRotationDegrees[9];
	glm::mat4 m_cubieRotationMatrices[3][3][3];
	glm::quat m_cubieRotationQuaternions[3][3][3];
	bool m_rotating;
};

