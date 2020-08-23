#pragma once
#include "Cubie.h"



class CubeModel {

private:

	//in logical order: 
	//	faces (left to right along x axis), 
	//	rows (bottom to top along y), 
	//	columns (back to front along z)
	// numbers should rise with distance from 0,0,0
	// left bottom back should be at 0,0,0
	
	Cubie cubies[3][3][3];

public:
	void CreateCube();
	void RotateSlice(Axis axis, int sliceNumber, bool rotateClockwise);
	void PrintCube();
};
