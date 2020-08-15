#include "Cubie.h"
#include <glm/gtx/rotate_vector.hpp>

Cubie::Cubie(CubieType type, int position[])
{
	this->type = type;
	if (type == CubieType::CENTER)
	{
		this->numberOfRelevantSides = 0;
	}
	else if (type == CubieType::MIDDLE)
	{
		this->numberOfRelevantSides = 1;
	}
	else if (type == CubieType::EDGE)
	{
		this->numberOfRelevantSides = 2;
	}
	else if (type == CubieType::CORNER)
	{
		this->numberOfRelevantSides = 3;
	}
	int facesAdded = 0;
	for (int i = 0; i < 3; i++)
	{
		Face face;
		face.color = "color";
		// if x = 0, face left
		// if x = 2, face right
		// if y = 0, face down
		// if y = 2, face up
		// if z = 0, face back
		// if z = 2, face front
		if (position[i] == 0) {
			if (i == 0) {
				face.facing = glm::vec3(-1.0, 0.0, 0.0);
			}
			else if (i == 1) {
				face.facing = glm::vec3(0.0, -1.0, 0.0);
			}
			else if (i == 2) {
				face.facing = glm::vec3(0.0, 0.0, -1.0);
			}
			relevantFaces[facesAdded] = face;
			facesAdded++;
		}
		else if (position[i] == 2) {
			if (i == 0) {
				face.facing = glm::vec3(1.0, 0.0, 0.0);
			}
			else if (i == 1) {
				face.facing = glm::vec3(0.0, 1.0, 0.0);
			}
			else if (i == 2) {
				face.facing = glm::vec3(0.0, 0.0, 1.0);
			}
			relevantFaces[facesAdded] = face;
			facesAdded++;
		}


	}

}

Cubie Cubie::RotatedCubie(Axis rotatedAround)
{
	for (int i = 0; i < numberOfRelevantSides; i++)
	{
		if (rotatedAround == Axis::X_AXIS) {
			relevantFaces[i].facing = glm::rotateX(relevantFaces[i].facing, (float)glm::radians(90));
		}
		else if (rotatedAround == Axis::Y_AXIS) {
			relevantFaces[i].facing = glm::rotateY(relevantFaces[i].facing, (float)glm::radians(90));
		}
		else if (rotatedAround == Axis::Z_AXIS) {
			relevantFaces[i].facing = glm::rotateZ(relevantFaces[i].facing, (float)glm::radians(90));
		}
	}
	return *this;
}
