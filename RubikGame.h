#pragma once
#include "GameInterface.h"
#include "CubieRenderer.h"
#include "InputSystem.h"
#include "CubeModel.h"
#include <glm/ext/quaternion_float.hpp>
#include <map>

class RubikGame :
	public GameInterface
{
public:

	virtual void Initialize(GLFWwindow* window);
	virtual void Render(float aspectRatio);
	virtual void ClearResources();
	virtual void Update(double deltaTime);

private:

	void RotateSlice(Axis axis, int sliceNumber, bool clockwise, bool mouseRotation);
	void SendRay();

	CubieRenderer m_cubieRenderer;
	InputSystem m_inputSystem;
	CubeModel m_cubeModel;


	glm::mat4 m_globalTransformation;
	glm::quat m_orientationQuaternion;
	int m_currentlyRotatedSlice;
	float m_degreesToRotate;
	float m_animationRotationAngle;
	float m_animationEndAngle;
	float m_animationSpeed;
	float m_sliceRotationDegrees[9];
	glm::vec3 m_cubeColors[3][3][3][6];
	Axis m_currentRotationAxis;
	bool m_clockwise;
	bool m_rotating;
	glm::vec3 m_initialContactPoint;
	glm::vec3 m_contactPlaneNormal;
	bool m_finishRotatingAfterRelease = false;
	bool m_freezeAutomaticRotation = false;

};

