#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H

#include "string"
#include "vector"
#include "iostream"
#include "limits"
#include "exceptions/MatrixException.h"
#include "exceptions/DefaultClassException.h"
#include "Matrix.h"
#include "matrixTypes/DiagMatrix.h"
#include "matrixTypes/SquareMatrix.h"
#include "matrixTypes/TriangularMatrix.h"
#include "matrixTypes/SingleMatrix.h"
#include "PCA.h"

using namespace std;

static vector<string> test_types = {
        "1. Usual matrices",
        "2. Single matrices",
        "3. Diagonal matrices",
        "4. Triangular matrices",
        "5. Vector methods",
        "6. Matrices methods",
        "7. Reading the matrix from a txt-file",
        "8. Write the matrix to a txt-file",
        "9. PCA"
};

void test();

#endif //MATRIX_TESTS_H
