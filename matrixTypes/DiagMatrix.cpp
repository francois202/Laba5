#include "DiagMatrix.h"
#include "../exceptions/MatrixException.h"
#include "../exceptions/DefaultClassException.h"


DiagMatrix::DiagMatrix(unsigned int dim, double default_value): SquareMatrix(dim) {
    for(int i = 0; i < dim; i++)
        this->data[i][i] = default_value;
}


double DiagMatrix::get(unsigned number) {
    try {
        return static_cast<Matrix*>(this)->get(number, number);
    } catch(DefaultClassException &exc)
    { throw exc; }
}

void DiagMatrix::set(unsigned int dim, double value) {
    try {
        static_cast<Matrix*>(this)->set(dim, dim, value);
    } catch (DefaultClassException exc)
    { throw exc; }
}

DiagMatrix DiagMatrix::operator*(double scale)
{
    DiagMatrix new_matrix = DiagMatrix(this->rows);
    for(int i = 0; i < this->rows; i++)
        new_matrix.data[i][i] = this->data[i][i] * scale;
    return new_matrix;
}

DiagMatrix DiagMatrix::operator*(const DiagMatrix &other_matrix)
{
    try {
        if(!DiagMatrix::isEqualDimension(*this, other_matrix))
            throw MatrixException(MatrixException::notEqualMatrices);
        DiagMatrix new_matrix = DiagMatrix(this->rows);
        for (int i = 0; i < this->rows; i++)
            new_matrix.data[i][i] = this->data[i][i] * other_matrix.data[i][i];
        return new_matrix;
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "operator*");
    }
}

DiagMatrix DiagMatrix::hadamardProduct(const DiagMatrix &matrix) {
    try {
        return (*this) * matrix;
    } catch (DefaultClassException exc)
    { throw exc; }
}


double DiagMatrix::get(unsigned int row, unsigned int col) {
    try {
        if(!DiagMatrix::isRowValid(*this, row))
            throw MatrixException(MatrixException::notDiagonalElement);
        return this->data[row][col];
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "get");
    }
}

void DiagMatrix::set(unsigned int row, unsigned int col, double value) {
    try {
        if(row != col or !DiagMatrix::isRowValid(*this, row))
            throw MatrixException(MatrixException::notDiagonalElement);
        this->data[row][col] = value;
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "set");
    }
}

double DiagMatrix::operator[](int index) {
    try {
        if(!DiagMatrix::isRowValid(*this, index))
            throw MatrixException(MatrixException::limitsViolated);
        return this->data[index][index];
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "operator[]");
    }
}



DiagMatrix DiagMatrix::groupOperation(const DiagMatrix &matrix1,
                                            const DiagMatrix &matrix2,
                                            bool op_type)
{
    try {
        if(!DiagMatrix::isEqualDimension(matrix1, matrix2))
            throw MatrixException(MatrixException::notEqualMatrices);
        DiagMatrix new_matrix = DiagMatrix(matrix1.rows);
        for(int i = 0; i < matrix1.rows; i++)
            new_matrix.data[i][i] = op_type ? matrix1.data[i][i] + matrix2.data[i][i] :
                                               matrix1.data[i][i] - matrix2.data[i][i];
        return new_matrix;

    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "groupOperation");
    }
}

DiagMatrix DiagMatrix::operator+(const DiagMatrix &matrix)
{
    try {
        return this->groupOperation(*this, matrix);
    } catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "operator+");
    }
}

DiagMatrix DiagMatrix::operator-(const DiagMatrix &matrix)
{
    try {
        return this->groupOperation(*this, matrix, false);
    } catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("DiagMatrix", "operator-");
    }
}
