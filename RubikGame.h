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
	bool m_rotating;
};

