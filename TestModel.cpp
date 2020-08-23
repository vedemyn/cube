#include "TestModel.h"

void TestModel::Initialize()
{
	m_cubeModel.CreateCube();
}

void TestModel::Render(float aspectRatio)
{
}

void TestModel::ClearResources()
{
}

void TestModel::Update(double deltaTime)
{
	m_cubeModel.PrintCube();
	m_cubeModel.RotateSlice(Axis::Z_AXIS, 2, true);
}
