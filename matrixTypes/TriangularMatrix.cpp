#include "TriangularMatrix.h"
#include "../exceptions/DefaultClassException.h"


TriangularMatrix::TriangularMatrix(unsigned int dim, bool t_type):
    SquareMatrix(dim), triangular_type(t_type) {};


vector<double> TriangularMatrix::operator[](unsigned index) {
    try {
        if(!TriangularMatrix::isRowValid(*this, index))
            throw MatrixException(MatrixException::limitsViolated);
        return this->data[index];
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("TriangularMatrix", "operator[]");
    }
}


void TriangularMatrix::set(unsigned int row, unsigned int col, double value) {
    try {
        if(value != 0) {
            if (triangular_type and col > row)
                throw MatrixException(MatrixException::notTriangularMatrixCell);
            if (!triangular_type and row > col)
                throw MatrixException("gegege");
            this->data[row][col] = value;
        }
    } catch (MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("TriangularMatrix", "set");
    }
}

double TriangularMatrix::get(unsigned int row, unsigned int col) {
    try {
        if(!TriangularMatrix::isCellValid(*this, row, col))
            throw MatrixException(MatrixException::limitsViolated);
        if((triangular_type and col > row) or (!triangular_type and row > col))
            return 0;
        return this->data[row][col];
    } catch (MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("TriangularMatrix", "get");
    }
}


TriangularMatrix TriangularMatrix::testMatrix(unsigned dim, bool t_type) {
    TriangularMatrix new_matrix = TriangularMatrix(dim, t_type);
    unsigned previous_sum = 0;
        for (int i = 0; i < dim; i++) {
            // If left triangular
            if(t_type) {
                for (int j = 0; j <= i; j++)
                    new_matrix.data[i][j] = previous_sum + j + 1;
                previous_sum += i + 1;
            // If right triangular
            } else {
                for(int j = i; j < dim; j++)
                    new_matrix.data[i][j] = previous_sum + j + 1;
                previous_sum += dim - i - 1;
            }
        }
    return new_matrix;
}