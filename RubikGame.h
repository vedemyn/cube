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

private:
	CubieRenderer m_cubieRenderer;
	InputSystem m_inputSystem;
	CubeModel m_cubeModel;
	

	glm::quat m_orientationQuaternion;
	float m_turningAngle;
};

