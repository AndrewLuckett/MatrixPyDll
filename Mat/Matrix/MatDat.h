/*
Author: Andrew Luckett
License: CC-BY

Header file to outline Matrix data type
*/

#pragma once

typedef unsigned long uint;

struct Size {
	uint height;
	uint width;
};

struct Matrix {
	Size size;
	double* dat;
};