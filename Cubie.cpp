#include "Cubie.h"
#include <glm/gtx/rotate_vector.hpp>

Cubie::Cubie(int position[])
{
	//cubie type can be determined by the number of 1s in the position
	// 3 == center, 2 == middle, 1 == edge, 0 == corner 
	colors.insert({ "RED", glm::vec3(1.0, 0.0, 0.0) });
	colors.insert({ "GREEN", glm::vec3(0.0f, 0.608f, 0.282f) });
	colors.insert({ "BLUE", glm::vec3(0.0f, 0.271f, 0.678f) });
	colors.insert({ "WHITE", glm::vec3(1.0f, 1.0f, 1.0f) });
	colors.insert({ "YELLOW", glm::vec3(1.0f, 0.835f, 0.0f) });
	colors.insert({ "ORANGE", glm::vec3(1.0f, 0.349f, 0.0f) });
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
				face.color = colors["ORANGE"];
			}
			else if (i == 1) {
				face.facing = glm::vec3(0.0, -1.0, 0.0);
				face.color = colors["YELLOW"];
			}
			else if (i == 2) {
				face.facing = glm::vec3(0.0, 0.0, -1.0);
				face.color = colors["BLUE"];
			}
			faces[facesAdded] = face;
			facesAdded++;
		}
		else if (position[i] == 2) {
			if (i == 0) {
				face.facing = glm::vec3(1.0, 0.0, 0.0);
				face.color = colors["RED"];
			}
			else if (i == 1) {
				face.facing = glm::vec3(0.0, 1.0, 0.0);
				face.color = colors["WHITE"];
			}
			else if (i == 2) {
				face.facing = glm::vec3(0.0, 0.0, 1.0);
				face.color = colors["GREEN"];
			}
			faces[facesAdded] = face;
			facesAdded++;
		}

	}

}

Cubie Cubie::RotatedCubie(Axis rotatedAround)
{
	for (int i = 0; i < numberOfRelevantSides; i++)
	{
		if (rotatedAround == Axis::X_AXIS) {
			faces[i].facing = glm::rotateX(faces[i].facing, (float)glm::radians(270.0)); //meine achsen gehen teilweise in eine andere richtung als die von gl, deswegen hier komische winkel
		}
		else if (rotatedAround == Axis::Y_AXIS) {
			faces[i].facing = glm::rotateY(faces[i].facing, (float)glm::radians(90.0)); 
		}
		else if (rotatedAround == Axis::Z_AXIS) {
			faces[i].facing = glm::rotateZ(faces[i].facing, (float)glm::radians(270.0));
		}
	}
	return *this;
}

glm::vec3 Cubie::FaceByFacing(glm::vec3 facing)
{
	for (int i = 0; i < numberOfRelevantSides; i++)
	{
		auto temp = faces[i].facing - facing;
		if (glm::length(temp) < 0.1f)
		{
			return faces[i].color;
		}
	}
	return glm::vec3(0.0f);
}
