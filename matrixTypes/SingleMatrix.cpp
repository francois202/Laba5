#include "SingleMatrix.h"


void SingleMatrix::fillByValue(double value) {
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            this->data[i][j] = value;
}

SingleMatrix::SingleMatrix(unsigned int dim, double value): SquareMatrix(dim) {
    this->fillByValue(value);
}
