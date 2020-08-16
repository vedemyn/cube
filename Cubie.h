#pragma once
#include <glm/vec3.hpp>
#include <string>

enum class Axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

struct Face {
	std::string color;
	//normal of the surface
	glm::vec3 facing = glm::vec3();
};

class Cubie
{
private:
	int numberOfRelevantSides = 0;
	Face relevantFaces[3];

public:
	Cubie() = default;
	Cubie(int position[]);
	Cubie RotatedCubie(Axis rotatedAround);
};

