/*
Author: Andrew Luckett
License: CC-BY

Header file to outline functions and types for dllmain.cpp
*/

#pragma once

#include <vector>

#ifdef TRUE //MATHLIBRARY_EXPORTS
	#define MAT_API __declspec(dllexport)
#else
	#define MAT_API __declspec(dllimport)
#endif

typedef unsigned int uint;

struct Size {
	uint height;
	uint width;
};

struct Matrix {
	Size size;
	double* dat;
};

extern "C" MAT_API Matrix * newMat(Size size, double value, bool random);
extern "C" MAT_API Matrix * generate(Size size, double* a);

extern "C" MAT_API Matrix* mult(Matrix* a, Matrix* b);
extern "C" MAT_API Matrix* add(Matrix* a, Matrix* b);
extern "C" MAT_API Matrix* sub(Matrix* a, Matrix* b);

extern "C" MAT_API bool equ(Matrix* a, Matrix* b);
extern "C" MAT_API bool del(Matrix* a);

extern "C" MAT_API Matrix* sca(Matrix* a, double v); //Scalar mult

extern "C" MAT_API Size getSize(Matrix* a);
extern "C" MAT_API double getValue(Matrix* a, uint b, uint c);