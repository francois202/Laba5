#ifndef MATRIX_TRIANGULAR_MATRIX_H
#define MATRIX_TRIANGULAR_MATRIX_H

#include "SquareMatrix.h"
#include "../exceptions/MatrixException.h"
#include "../exceptions/BasicException.h"


class TriangularMatrix: public SquareMatrix {
public:
    TriangularMatrix(unsigned dim, bool t_type = true);
    void set(unsigned row, unsigned col, double value) override;
    double get(unsigned row, unsigned col) override;
    vector<double> operator[](unsigned index);
    static TriangularMatrix testMatrix(unsigned dim, bool t_type = 1);
protected:
    // true - left, false - right
    bool triangular_type;
};


#endif //MATRIX_TRIANGULAR_MATRIX_H
