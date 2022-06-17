#ifndef MATRIX_SINGLE_MATRIX_H
#define MATRIX_SINGLE_MATRIX_H

#include "SquareMatrix.h"

class SingleMatrix: public SquareMatrix {
public:
    // Other constructor
    SingleMatrix(unsigned dim, double value = 1);

protected:
    void fillByValue(double value);
};


#endif //MATRIX_SINGLE_MATRIX_H
