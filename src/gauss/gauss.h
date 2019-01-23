#ifndef _GAUSS_H_IS_INCLUDED_
#define _GAUSS_H_IS_INCLUDED_

#include "../matrix/matrix.h"

// Eliminates the matrix
// Returns 0 if matrix was eliminated correctly and 1 if there was division by zero
int eliminate(Matrix *matrix, Matrix *b);

// Backward substitutes the matrix calculating x'es
void backsubst(Matrix *matrix, Matrix *x, Matrix *b);

#endif