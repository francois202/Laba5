#ifndef MATRIX_SQUARE_MATRIX_H
#define MATRIX_SQUARE_MATRIX_H

#include "../Matrix.h"

class SquareMatrix: public Matrix {
public:
    SquareMatrix(unsigned dim): Matrix(dim, dim) {};
};


#endif //MATRIX_SQUARE_MATRIX_H
