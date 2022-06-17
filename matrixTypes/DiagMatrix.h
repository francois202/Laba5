#ifndef MATRIX_DIAG_MATRIX_H
#define MATRIX_DIAG_MATRIX_H

#include "SquareMatrix.h"

class DiagMatrix: public SquareMatrix {
public:
    explicit DiagMatrix(unsigned dim, double default_value = 1);

    DiagMatrix operator+(const DiagMatrix& other_matrix);
    DiagMatrix operator-(const DiagMatrix& other_matrix);
    DiagMatrix operator*(const DiagMatrix& other_matrix);
    DiagMatrix operator*(double scale);
    double operator[](int index);
    DiagMatrix hadamardProduct(const DiagMatrix& matrix);

    void set(unsigned row, unsigned col, double value) override;
    double get(unsigned row, unsigned col) override;
    double get(unsigned dim);
    void set(unsigned dim, double value);
private:
    static DiagMatrix groupOperation(const DiagMatrix& matrix1, const DiagMatrix& matrix2, bool op_type = true);
};

#endif //MATRIX_DIAG_MATRIX_H
