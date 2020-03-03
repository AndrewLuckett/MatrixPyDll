// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Matrix.h"
#include <array>

MAT_API Matrix* newMat(Size size, double value, bool random) {
	Matrix* out = new Matrix();
	out->size = size;
	int j = size.height * size.width;
	out->dat = new double[j];
	for (int i = 0; i < j; i++) {
		out->dat[i] = value;
	}
	return out;
}

MAT_API Matrix* generate(Size size, double* a) {
	Matrix* out = new Matrix();
	int j = size.height * size.width;
	out->size = size;
	out->dat = new double[j];
	for (int i = 0; i < j; i++) {
		out->dat[i] = a[i];
	}
	return out;
}


MAT_API Matrix* mult(Matrix* a, Matrix* b) {
	return nullptr;
}

MAT_API Matrix* add(Matrix* a, Matrix* b) {
	return nullptr;
}

MAT_API Matrix* sub(Matrix* a, Matrix* b) {
	return nullptr;
}

MAT_API double getValue(Matrix* a, uint b, uint c) {
	int ind = (b - 1) * a->size.width + c - 1;
	return a->dat[ind];
}

MAT_API bool equ(Matrix* a, Matrix* b) {
	return false;
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

MAT_API Matrix* neg(Matrix* a) {
	return nullptr;
}

MAT_API Matrix* sca(Matrix* a, double v) {
	return nullptr;
}

MAT_API Size getSize(Matrix* a) {
	return a->size;
}
