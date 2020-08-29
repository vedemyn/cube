#include "CubeModel.h"
#include <iostream>

void CubeModel::CreateCube()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				int position[] = { x, y, z };
				cubies[x][y][z] = Cubie(position);
			}
		}
	}
}

void CubeModel::RotateSlice(Axis axis, int sliceNumber, bool rotateClockwise)
{
	//if we rotate clockwise, we only rotate once, otherwise we rotate 3 times which 
	//results in the same state as 1 counter-clockwise rotation
	int numOfClockwiseRotations = (rotateClockwise) ? 1 : 3;

	//check for input slices correctness

	for (int i = 0; i < numOfClockwiseRotations; i++)
	{
		//bei allen folgenden rotationen wird angenommen,
		//dass man entlang der achse schaut um die rotiert wird
		Cubie tempCubie;
		if (axis == Axis::X_AXIS)
		{

			//this means all the cubies that are rotated will not change in their
			//x-position in the array


			//total of 8 cubies change position, 9 cubies in selection
			// 2 cases: corners and faces
			//the corners
			tempCubie = cubies[sliceNumber][0][0].RotatedCubie(axis);
			cubies[sliceNumber][0][0] = cubies[sliceNumber][2][0].RotatedCubie(axis);
			cubies[sliceNumber][2][0] = cubies[sliceNumber][2][2].RotatedCubie(axis);
			cubies[sliceNumber][2][2] = cubies[sliceNumber][0][2].RotatedCubie(axis);
			cubies[sliceNumber][0][2] = tempCubie;

			//the faces
			tempCubie = cubies[sliceNumber][0][1].RotatedCubie(axis);
			cubies[sliceNumber][0][1] = cubies[sliceNumber][1][0].RotatedCubie(axis);
			cubies[sliceNumber][1][0] = cubies[sliceNumber][2][1].RotatedCubie(axis);
			cubies[sliceNumber][2][1] = cubies[sliceNumber][1][2].RotatedCubie(axis);
			cubies[sliceNumber][1][2] = tempCubie;

			//middle cubie stays the same, no need to do anything

		}
		else if (axis == Axis::Y_AXIS)
		{
			//this means they will not change in their 
			//y-position in the array
			//the corners
			tempCubie = cubies[0][sliceNumber][0].RotatedCubie(axis);
			cubies[0][sliceNumber][0] = cubies[2][sliceNumber][0].RotatedCubie(axis);
			cubies[2][sliceNumber][0] = cubies[2][sliceNumber][2].RotatedCubie(axis);
			cubies[2][sliceNumber][2] = cubies[0][sliceNumber][2].RotatedCubie(axis);
			cubies[0][sliceNumber][2] = tempCubie;

			//the faces
			tempCubie = cubies[0][sliceNumber][1].RotatedCubie(axis);
			cubies[0][sliceNumber][1] = cubies[1][sliceNumber][0].RotatedCubie(axis);
			cubies[1][sliceNumber][0] = cubies[2][sliceNumber][1].RotatedCubie(axis);
			cubies[2][sliceNumber][1] = cubies[1][sliceNumber][2].RotatedCubie(axis);
			cubies[1][sliceNumber][2] = tempCubie;

		}
		else if (axis == Axis::Z_AXIS)
		{
			//this means they will not change in their 
			//z-position in the array
			//the corners
			tempCubie = cubies[0][0][sliceNumber].RotatedCubie(axis);
			cubies[0][0][sliceNumber] = cubies[2][0][sliceNumber].RotatedCubie(axis);
			cubies[2][0][sliceNumber] = cubies[2][2][sliceNumber].RotatedCubie(axis);
			cubies[2][2][sliceNumber] = cubies[0][2][sliceNumber].RotatedCubie(axis);
			cubies[0][2][sliceNumber] = tempCubie;

			//the faces
			tempCubie = cubies[0][1][sliceNumber].RotatedCubie(axis);
			cubies[0][1][sliceNumber] = cubies[1][0][sliceNumber].RotatedCubie(axis);
			cubies[1][0][sliceNumber] = cubies[2][1][sliceNumber].RotatedCubie(axis);
			cubies[2][1][sliceNumber] = cubies[1][2][sliceNumber].RotatedCubie(axis);
			cubies[1][2][sliceNumber] = tempCubie;

		}

	}
	//PrintCube();
}

Cubie CubeModel::getCubie(int x, int y, int z)
{
	return cubies[x][y][z];
}
/* wurde benutzt um das modell zu testen, mit farben die strings waren - jetzt nicht mehr nötig
void CubeModel::PrintCube()
{ 
	std::cout << "Front Side: " << std::endl;
	std::cout << " [ " << cubies[0][2][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << " [ " << cubies[1][2][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << " [ " << cubies[2][2][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][1][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << " [ " << cubies[1][1][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << " [ " << cubies[2][1][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][0][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << " [ " << cubies[1][0][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << " [ " << cubies[2][0][2].FaceByFacing(glm::vec3(0.0f, 0.0f, 1.0f)) << " ] " << std::endl;

	std::cout << "Top Side: " << std::endl;
	std::cout << " [ " << cubies[0][2][0].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << " [ " << cubies[1][2][0].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << " [ " << cubies[2][2][0].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][2][1].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << " [ " << cubies[1][2][1].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << " [ " << cubies[2][2][1].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][2][2].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << " [ " << cubies[1][2][2].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << " [ " << cubies[2][2][2].FaceByFacing(glm::vec3(0.0f, 1.0f, 0.0f)) << " ] " << std::endl;

	std::cout << "Back Side: " << std::endl;
	std::cout << " [ " << cubies[0][0][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << " [ " << cubies[1][0][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << " [ " << cubies[2][0][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][1][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << " [ " << cubies[1][1][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << " [ " << cubies[2][1][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][2][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << " [ " << cubies[1][2][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << " [ " << cubies[2][2][0].FaceByFacing(glm::vec3(0.0f, 0.0f, -1.0f)) << " ] " << std::endl;

	std::cout << "Bottom Side: " << std::endl;
	std::cout << " [ " << cubies[0][0][2].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << " [ " << cubies[1][0][2].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << " [ " << cubies[2][0][2].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][0][1].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << " [ " << cubies[1][0][1].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << " [ " << cubies[2][0][1].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][0][0].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << " [ " << cubies[1][0][0].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << " [ " << cubies[2][0][0].FaceByFacing(glm::vec3(0.0f, -1.0f, 0.0f)) << " ] " << std::endl;

	std::cout << "Left Side: " << std::endl;
	std::cout << " [ " << cubies[0][2][0].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[0][2][1].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[0][2][2].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][1][0].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[0][1][1].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[0][1][2].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[0][0][0].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[0][0][1].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[0][0][2].FaceByFacing(glm::vec3(-1.0f, 0.0f, 0.0f)) << " ] " << std::endl;

	std::cout << "Right Side: " << std::endl;
	std::cout << " [ " << cubies[2][2][2].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[2][2][1].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[2][2][0].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[2][1][2].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[2][1][1].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[2][1][0].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << std::endl;
	std::cout << " [ " << cubies[2][0][2].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[2][0][1].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << " [ " << cubies[2][0][0].FaceByFacing(glm::vec3(1.0f, 0.0f, 0.0f)) << " ] " << std::endl;

	std::cout << "====================================================================================" << std::endl;
	
}
*/
