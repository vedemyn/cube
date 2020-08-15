#pragma once
#include <glm/vec3.hpp>
#include <string>
//cubie type can be determined by the number of 1s in the position??
// 3 == center, 2 == middle, 1 == edge, 0 == corner lol
enum class CubieType {
	CENTER,
	MIDDLE,
	EDGE,
	CORNER
};

enum class Axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

struct Face {
	std::string color;
	//normal of the surface
	glm::vec3 facing;
};

class Cubie
{
private:
	CubieType type;
	int numberOfRelevantSides;
	Face relevantFaces[3];

public:
	Cubie(CubieType type, int position[]);
	Cubie RotatedCubie(Axis rotatedAround);
};

