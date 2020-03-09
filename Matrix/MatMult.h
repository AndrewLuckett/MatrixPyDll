/*
Author: Andrew Luckett
License: CC-BY

Header file to outline Matrix multiplication functions
*/

#pragma once

#include "MatDat.h"

namespace MatrixMult {
	Matrix* multiply(Matrix* a, Matrix* b);

	Matrix* strass(Matrix* a, Matrix* b);
	Matrix* naive(Matrix* a, Matrix* b);
	Matrix* byn1(Matrix* a, Matrix* b);
}