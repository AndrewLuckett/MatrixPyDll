/*
Author: Andrew Luckett
License: CC-BY

This file includes a series of functions to enable matrix based mathematics.
Potentially reusable in other C code works.
Primarily created to produce Matrix.dll to create faster python matrix calculations.
*/
#include "pch.h"
#include "Matrix.h"
#include "MatMult.h"

MAT_API Matrix* newMat(Size size, double value, bool random) {
	Matrix* out = new Matrix();

	out->size = size;
	uint j = size.height * size.width;
	out->dat = new double[j];

	for (uint i = 0; i < j; i++) {
		out->dat[i] = value;
	}

	return out;
}

MAT_API Matrix* generate(Size size, double* a) { //python only version
	Matrix* out = new Matrix();
	
	out->size = size;
	int j = size.height * size.width;
	double* newDat = new double[j];
	//Using newDat is necessary for when python calls this func
	//Otherwise out->dat = a could be used

	for (int i = 0; i < j; i++) {
		newDat[i] = a[i];
	}
	out->dat = newDat;
	
	return out;
}

Matrix* intGenerate(Size size, double* a) { //python only version
	Matrix* out = new Matrix();
	out->size = size;
	out->dat = a;

	return out;
}


MAT_API Matrix* mult(Matrix* a, Matrix* b) {
	return MatrixMult::multiply(a, b);
}

MAT_API Matrix* add(Matrix* a, Matrix* b) {
	if (a->size.height != b->size.height || a->size.width != b->size.width) {
		return nullptr;
	}

	uint j = a->size.height * a->size.width;
	double* newDat = new double[j];

	for (uint i = 0; i < j; i++) {
		newDat[i] = a->dat[i] + b->dat[i];
	}

	return intGenerate(a->size,newDat);
}

MAT_API Matrix* sub(Matrix* a, Matrix* b) {
	if (a->size.height != b->size.height || a->size.width != b->size.width) {
		return nullptr;
	}

	uint j = a->size.height * a->size.width;
	double* newDat = new double[j];

	for (uint i = 0; i < j; i++) {
		newDat[i] = a->dat[i] - b->dat[i];
	}

	return intGenerate(a->size, newDat);
}

MAT_API double getValue(Matrix* a, uint b, uint c) {
	uint ind = (b - 1) * a->size.width + c - 1;
	return a->dat[ind];
}

MAT_API bool equ(Matrix* a, Matrix* b) {
	if (a->size.height != b->size.height || a->size.width != b->size.width) {
		return false;
	}

	uint j = a->size.height * a->size.width;

	for (uint i = 0; i < j; i++) {
		if (a->dat[i] != b->dat[i]) {
			return false;
		}
	}

	return true;
}

MAT_API bool del(Matrix* a) {
	try {
		delete a->dat;
		delete a;
		return true;
	} catch (...) {
		return false;
	}
}

MAT_API Matrix* sca(Matrix* a, double v) {
	uint j = a->size.height * a->size.width;
	double* newDat = new double[j];

	for (uint i = 0; i < j; i++) {
		newDat[i] = a->dat[i] * v;
	}

	return intGenerate(a->size, newDat);
}

MAT_API Size getSize(Matrix* a) {
	return a->size;
}
