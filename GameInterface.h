#pragma once
class GameInterface
{
public:
	virtual void Initialize() {};

	virtual void Update(double deltaTime) {};

	virtual void Render(float aspectRatio) {};

	virtual void ClearResources() {};
};

