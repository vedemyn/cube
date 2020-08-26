#pragma once
#include <glm/vec3.hpp>
#include <string>
#include <map>

enum class Axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

struct Face {
	glm::vec3 color;
	//normal of the surface
	glm::vec3 facing = glm::vec3();
};

class Cubie
{
private:
	int numberOfRelevantSides = 0;
	Face faces[6];
	std::map<std::string, glm::vec3> colors;

public:
	Cubie() = default;
	Cubie(int position[]);
	Cubie RotatedCubie(Axis rotatedAround);
	glm::vec3 FaceByFacing(glm::vec3 facing);
};

