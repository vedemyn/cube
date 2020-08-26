#include "Cubie.h"
#include <glm/gtx/rotate_vector.hpp>

Cubie::Cubie(int position[])
{
	//cubie type can be determined by the number of 1s in the position
	// 3 == center, 2 == middle, 1 == edge, 0 == corner lol
	int numberOfOnesInPositionIndex = 0;
	for (int i = 0; i < 3; i++)
	{
		if (position[i] == 1) {
			numberOfOnesInPositionIndex++;
		}
	}
	numberOfRelevantSides = 3 - numberOfOnesInPositionIndex;
		
	
	int facesAdded = 0;
	for (int i = 0; i < 3; i++)
	{
		Face face;
		// if x = 0, face left
		// if x = 2, face right
		// if y = 0, face down
		// if y = 2, face up
		// if z = 0, face back
		// if z = 2, face front
		if (position[i] == 0) {
			if (i == 0) {
				face.facing = glm::vec3(-1.0, 0.0, 0.0);
				face.color = "left";
			}
			else if (i == 1) {
				face.facing = glm::vec3(0.0, -1.0, 0.0);
				face.color = "down";
			}
			else if (i == 2) {
				face.facing = glm::vec3(0.0, 0.0, -1.0);
				face.color = "back";
			}
			relevantFaces[facesAdded] = face;
			facesAdded++;
		}
		else if (position[i] == 2) {
			if (i == 0) {
				face.facing = glm::vec3(1.0, 0.0, 0.0);
				face.color = "right";
			}
			else if (i == 1) {
				face.facing = glm::vec3(0.0, 1.0, 0.0);
				face.color = "up";
			}
			else if (i == 2) {
				face.facing = glm::vec3(0.0, 0.0, 1.0);
				face.color = "front";
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
			relevantFaces[i].facing = glm::rotateX(relevantFaces[i].facing, (float)glm::radians(270.0)); //apparently this is counter-clockwise in glm, so 270 instead of 90
		}
		else if (rotatedAround == Axis::Y_AXIS) {
			relevantFaces[i].facing = glm::rotateY(relevantFaces[i].facing, (float)glm::radians(90.0)); //axes are brainfuck
		}
		else if (rotatedAround == Axis::Z_AXIS) {
			relevantFaces[i].facing = glm::rotateZ(relevantFaces[i].facing, (float)glm::radians(270.0));
		}
	}
	return *this;
}

std::string Cubie::FaceByFacing(glm::vec3 facing)
{
	for (int i = 0; i < numberOfRelevantSides; i++)
	{
		auto temp = relevantFaces[i].facing - facing;
		if (glm::length(temp) < 0.1f)
		{
			return relevantFaces[i].color;
		}
	}
	return "none";
}
