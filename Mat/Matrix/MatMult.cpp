/*
Author: Andrew Luckett
License: CC-BY

This file includes a series of functions to enable matrix multiplication.
Potentially reusable in other C code works.
Primarily created to enable matrix multiplication in dllmain.
*/
#include "pch.h"
#include "MatMult.h"
#include "Matrix.h"

Matrix* MatrixMult::multiply(Matrix* a, Matrix* b) { //TODO
	if (a->size.width != b->size.height) {
		return nullptr;
	}

	return naive(a, b);
}

Matrix* MatrixMult::strass(Matrix* a, Matrix* b) { //TODO
	return nullptr;
}

Matrix* MatrixMult::naive(Matrix* a, Matrix* b) { //TODO
	Size size = { a->size.height,b->size.width };
	uint j = a->size.height * b->size.width;
	double* dat = new double[j];

	for (uint outrow = 0; outrow < a->size.height; outrow++) {
		for (uint outCol = 0; outCol < b->size.width; outCol++) {
			double sum = 0;
			for (uint offset = 0; offset < a->size.width; offset++) {
				sum += getValue(a, outrow + 1, offset + 1) * getValue(b, offset + 1, outCol + 1);
			}
			dat[outrow * size.width + outCol] = sum;
		}
	}
	return intGenerate(size,dat);
}

Matrix* MatrixMult::byn1(Matrix* a, Matrix* b) { //TODO
	return nullptr;
}
