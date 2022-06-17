#ifndef MATRIX_PCA_H
#define MATRIX_PCA_H
#include "Matrix.h"
#include <string>
#include <map>

class PCA : public Matrix {

public:
    // Basic constructor
    PCA(unsigned rows, unsigned cols) : Matrix(rows, cols) {};

    // Empty matrix
    PCA() : Matrix() {};

    void operator-=(const Matrix& matrix);

    // Initialize be vectors
    PCA(vector<vector<double>> matrix_data) : Matrix(matrix_data) {};
    PCA(PCA* matrix) : Matrix(matrix) {};
    void scaling();
    map<string, Matrix> NEPAL();
    static Matrix range(Matrix T);
    static Matrix remainders(Matrix E);
    static double TRV(Matrix remainders, map<string, unsigned> size);
    double ERV(map<string, Matrix> nepals);
private:
    double colStd(unsigned num);
};
#endif //MATRIX_PCA_H
