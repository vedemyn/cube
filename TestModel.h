#pragma once
#include "GameInterface.h"
#include "CubeModel.h"

class TestModel:
	public GameInterface
{
public:

	virtual void Initialize();
	virtual void Render(float aspectRatio);
	virtual void ClearResources();
	virtual void Update(double deltaTime);

private:
	CubeModel m_cubeModel;

	float m_turningAngle;
};

