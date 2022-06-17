#ifndef MATRIX_MATRIX_EXCEPTION_H
#define MATRIX_MATRIX_EXCEPTION_H

#include "BasicException.h"

class MatrixException: public BasicException {
public:
    explicit MatrixException(string msg);
    explicit MatrixException(): BasicException() {};
    static const char* limitsViolatedErr();
    static const char* notSquareMatrixErr();
    static const char* notEqualMatricesErr();
    static const char* notDiagonalElementErr();
    static const char* cannotBeMultipliedErr();
    static const char* notTriangularMatrixCellErr();
    static const char* notVectorErr();
    static const char* notDoubleValueErr();
    static const char* notCorrectMatrixErr();
    static const char* emptyMatrixErr();


    static string limitsViolated;
    static string notSquareMatrix;
    static string notEqualMatrices;
    static string notDiagonalElement;
    static string cannotBeMultiplied;
    static string notTriangularMatrixCell;
    static string notVector;
    static string notDoubleValue;
    static string notCorrectMatrix;
    static string emptyMatrix;
};

#endif //MATRIX_MATRIX_EXCEPTION_H
