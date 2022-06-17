#include <iostream>
#include <vector>
#include "math.h"
#include "Matrix.h"
#include "exceptions/MatrixException.h"
#include "exceptions/DefaultClassException.h"
#include "matrixTypes/DiagMatrix.h"


using namespace std;


Matrix::Matrix(Matrix *matrix)
{
    this->rows = matrix->rows;
    this->cols = matrix->cols;
    for(int i = 0; i < matrix->rows; i++)
    {
        vector<double> row;
        for(int j = 0; j < matrix->cols; j++)
        {
            row.push_back(matrix->data[i][j]);
        }
        this->data.push_back(row);
    }
}

// Empty matrix
Matrix::~Matrix()
{
    this->clear();
}

Matrix::Matrix() {}

Matrix::Matrix(unsigned rows, unsigned cols)
{
    this->rows = rows;
    this->cols = cols;
    for(int i = 0; i < rows; i++)
    {
        vector<double> new_row(cols);
        this->data.push_back(new_row);
    }
}

Matrix::Matrix(vector<vector<double>> matrix_data)
{
    fill_matrix(matrix_data);
}

void Matrix::clear()
{
    for(int i = 0; i < this->rows; i++)
    {
        this->data[i].clear();
    }
    this->data.clear();
    this->rows = 0;
    this->cols = 0;
}

void Matrix::fill_matrix(vector<vector<double>> matrix_data)
{
    this->clear();

    int row_length = -1;
    try
    {
        for (auto &row: matrix_data)
        {
            if (row.size() == 0)
            {
                throw MatrixException(MatrixException::emptyMatrix);
            }
            if (row_length == -1)
            {
                row_length = row.size();
            }
            if (row_length != row.size())
            {
                throw MatrixException(MatrixException::notCorrectMatrix);
            }
            this->data.push_back(row);
        }
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        this->clear();
        throw DefaultClassException("Matrix", "fill_matrix");
    }
    this->rows = matrix_data.size();
    this->cols = row_length;
}


// Getters for basic properties


/**
 *
 * @tparam T
 * @param row
 * @param col
 * @return
 */
double Matrix::get(unsigned row, unsigned col)
{
    try
    {
        if(!this->isCellValid(*this, row, col))
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        return this->data[row][col];
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "get");
    }
}

void Matrix::set(unsigned row, unsigned col, double value)
{
    try
    {
        if(!this->isCellValid(*this, row, col))
            throw MatrixException(MatrixException::limitsViolated);
        this->data[row][col] = value;
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "set");
    }
}

Matrix Matrix::groupOperation(const Matrix &matrix1, const Matrix &matrix2, bool op_type)
{
    try
    {
        if(!this->isEqualDimension(matrix1, matrix2))
        {
            throw MatrixException(MatrixException::notEqualMatrices);
        }
        unsigned g_rows = matrix1.rows;
        unsigned g_cols = matrix2.cols;

        Matrix new_matrix(g_rows, g_cols);

        vector<vector<double>> m1_data = matrix1.data;
        vector<vector<double>> m2_data = matrix2.data;

        for(int i = 0; i < g_rows; i++)
        {
            for (int j = 0; j < g_cols; j++)
            {
                new_matrix[i][j] = op_type ? m1_data[i][j] + m2_data[i][j] : m1_data[i][j] - m2_data[i][j];
            }
        }
        return new_matrix;
    }
    catch (MatrixException exc)
    {
        throw exc;
    }
}

Matrix Matrix::operator+(const Matrix &other_matrix)
{
    try {
        return this->groupOperation(*this, other_matrix);
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "operator+");
    }
}

Matrix Matrix::operator-(const Matrix &other_matrix)
{
    try {
        return this->groupOperation(*this, other_matrix, 0);
    } catch(MatrixException exc) {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "operator-");
    }
}

Matrix Matrix::operator*(double scale)
{
    Matrix new_matrix = Matrix(this);
    for(int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            new_matrix.data[i][j] *= scale;
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*=(double scale)
{
    for(int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->data[i][j] *= scale;
        }
    }
    return this;
}

Matrix Matrix::operator/(double scale)
{
    Matrix new_matrix = Matrix(this);
    for(int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            new_matrix.data[i][j] /= scale;
        }
    }
    return new_matrix;
}

Matrix Matrix::operator/=(double scale)
{
    for(int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->data[i][j] /= scale;
        }
    }
    return this;
}

Matrix Matrix::operator*(const Matrix& other_matrix)
{
    try
    {
        if(!this->canBeMultiple(*this, other_matrix))
        {
            throw MatrixException(MatrixException::cannotBeMultiplied);
        }
        Matrix new_matrix  = Matrix(this->rows, other_matrix.cols);
        for(int o_col = 0; o_col < other_matrix.cols; o_col++)
        {
            for (int row = 0; row < this->rows; row++)
            {
                double vector_product = 0;
                for (int col = 0; col < this->cols; col++)
                {
                    vector_product += this->data[row][col] * other_matrix.data[col][o_col];
                }
                new_matrix.data[row][o_col] = vector_product;
            }
        }
        return new_matrix;
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "operator*");
    }
}

vector<double>& Matrix::operator[](int index)
{
    try
    {
        if(!Matrix::isRowValid(*this, index))
            throw MatrixException(MatrixException::limitsViolated);
        return this->data[index];
    }
    catch (MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "operator[]");
    }
}

Matrix Matrix::testMatrix(int rows, int cols)
{
    Matrix new_matrix = Matrix(rows, cols);
    for(int i = 0; i < rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            new_matrix.data[i][j - 1] = cols * i + j;
        }
    }
    return new_matrix;
}

Matrix Matrix::testVector(unsigned dim, bool isVertical)
{
    Matrix new_matrix = isVertical ? Matrix(dim, 1) : Matrix(1, dim);
    for(int i = 0; i < dim; i++)
    {
        if (isVertical)
        {
            new_matrix[i][0] = i + 1;
        }
        else
        {
            new_matrix[0][i] = i + 1;
        }
    }
    return new_matrix;
}

Matrix Matrix::testVerticalVector(unsigned rows)
{ return Matrix::testVector(rows); }

Matrix Matrix::testHorizontalVector(unsigned cols)
{ return Matrix::testVector(cols, false); }

Matrix Matrix::hadamardProduct(const Matrix &other_matrix)
{
    try {
        if (!this->isEqualDimension(*this, other_matrix))
        {
            throw MatrixException(MatrixException::notEqualMatrices);
        }
        Matrix new_matrix = Matrix(this->rows, this->cols);
        for(int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                new_matrix.data[i][j] = this->data[i][j] * other_matrix.data[i][j];
            }
        }
        return new_matrix;
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "hadamardProduct");
    }
}


double Matrix::trace()
{
    try
    {
        if(!Matrix::isSquareMatrix(*this))
        {
            throw MatrixException(MatrixException::notSquareMatrix);
        }
        double trace = 0;
        for(int i = 0; i < this->rows; i++)
        {
            trace += this->data[i][i];
        }
        return trace;
    }
    catch(MatrixException exc)
    {
        throw DefaultClassException("Matrix", "trace");
    }
}

double Matrix::productTrace()
{
    try
    {
        if(!Matrix::isSquareMatrix(*this))
        {
            throw MatrixException(MatrixException::notSquareMatrix);
        }
        double product_trace = 1;
        for(int i = 0; i < this->rows; i++)
        {
            product_trace *= this->data[i][i];
        }
        return product_trace;
    }
    catch(MatrixException exc)
    {
        throw DefaultClassException("Matrix", "productTrace");
    }
}



double Matrix::scalarProduct(const Matrix& matrix)
{
    try
    {
        if(!(Matrix::isVector(*this) and Matrix::isVector(matrix)))
        {
            throw MatrixException(MatrixException::notVector);
        }
        // If both matrices are vectors - product of matrix are similar operation with same exceptions
        return (*this * matrix).data[0][0];
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "scalarProduct");
    }
}

double Matrix::EuclideanNorm() const
{
    try
    {
        if(!Matrix::isVector(*this))
        {
            throw MatrixException(MatrixException::notVector);
        }
        double norm = 0;

        if(Matrix::isVerticalVector(*this))
        {
            for(int i = 0; i < this->rows; i++)
            {
                norm += pow(this->data[i][0], 2);
            }
        }
        if(Matrix::isHorizontalVector(*this))
        {
            for (int i = 0; i < this->cols; i++)
            {
                norm += pow(this->data[0][i], 2);
            }
        }
        return sqrt(norm);

    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "ChebishevNorm");
    }
}

double Matrix::maxValueOfVector()
{
    try
    {
        if(!Matrix::isVector(*this))
        {
            throw MatrixException(MatrixException::notVector);
        }
        double max_value = this->data[0][0];

        if(Matrix::isVerticalVector(*this))
        {
            for (int i = 0; i < this->rows; i++)
            {
                if (max_value < this->data[i][0])
                {
                    max_value = this->data[i][0];
                }
            }
        }
        if(Matrix::isHorizontalVector(*this))
        {
            for (int i = 0; i < this->cols; i++)
            {
                if (max_value < this->data[0][i])
                {
                    max_value = this->data[0][i];
                }
            }
        }
        return max_value;

    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "maxItemOfVector");
    }
}

double Matrix::ChebishevNorm()
{
    try
    {
        if(!Matrix::isVector(*this))
        {
            throw MatrixException(MatrixException::notVector);
        }
        double max_value = this->maxValueOfVector();
        return abs(max_value);
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "ChebishevNorm");
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "ChebishevNorm");
    }
}

double Matrix::FrobeniousNorm()
{
    double norm_value = 0;
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            norm_value += pow(this->data[i][j], 2);
        }
    }
    return sqrt(norm_value);
}

void Matrix::scaleRow(unsigned int row, double scale)
{
    try
    {
        if(!Matrix::isRowValid(*this, row))
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
            for(int i = 0; i < this->cols; i++)
            {
                this->data[row][i] *= scale;
            }
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "scaleRow");
    }
}

void Matrix::subtractRow(unsigned int from, unsigned int which, double scale)
{
    try
    {
        if(!(Matrix::isRowValid(*this, from) and Matrix::isRowValid(*this, which)))
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        for(int i = 0; i < this->cols; i++)
        {
            this->data[from][i] -= this->data[which][i] * scale;
        }
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "subtractRow");
    }
}


void Matrix::replaceRows(unsigned int first_row, unsigned int second_row)
{
    try
    {
        if(!(Matrix::isRowValid(*this, first_row) &&
             Matrix::isRowValid(*this, second_row)))
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        for(int i = 0; i < this->cols; i++)
        {
            double swap_item = this->data[first_row][i];
            this->data[first_row][i] = this->data[second_row][i];
            this->data[second_row][i] = swap_item;
        }
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "replaceRows");
    }
}

double Matrix::determineOfMatrix()
{
    try {
        if (!Matrix::isSquareMatrix(*this))
        {
            throw MatrixException(MatrixException::notSquareMatrix);
        }
        // Sign of the matrix (need to reaction on row swapping)
        short sign = 1;
        Matrix copy_matrix = Matrix(this);
        // Go through all columns
        for(int i = 0; i < copy_matrix.cols; i++)
        {
            // For every step observe every row
            for(int j = i; j < copy_matrix.rows; j++)
            {
                // If encountered not null first item in row - start Gaussean optimization
                if(copy_matrix[j][i] != 0)
                {
                    sign *= -1;
                    copy_matrix.replaceRows(j, i);
                    for(int k = i + 1; k < this->rows; k++)
                    {
                        copy_matrix.subtractRow(k, i, copy_matrix[k][i] / copy_matrix[i][i]);
                    }
                    break;
                }
            }
        }
        return sign * copy_matrix.productTrace();
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "determineOfMatrix");
    }
}

Matrix Matrix::makeRightTriangular()
{
    unsigned min_dim = this->rows > this->cols ? this->cols : this->rows;
    Matrix copy_matrix = Matrix(this);
    for(int i = 0; i < min_dim; i++)
    {
        for(int j = i; j < min_dim; j++)
        {
            if(copy_matrix[j][i] != 0) {
                copy_matrix.replaceRows(j, i);
                for (int k = i + 1; k < min_dim; k++)
                {
                    copy_matrix.subtractRow(k, i, copy_matrix[k][i] / copy_matrix[i][i]);
                }
                break;
            }
        }
    }
    return copy_matrix;
}

Matrix Matrix::makeLeftTriangular()
{
    Matrix copy_matrix = Matrix(this);
    unsigned min_dim = this->rows > this->cols ? this->cols : this->rows;
    for(int i = min_dim - 1; i >= 0; i--)
    {
        for(int j = i; j >= 0; j--)
        {
            if(copy_matrix[j][i] != 0) {
                copy_matrix.replaceRows(j, i);
                for (int k = i - 1; k >= 0; k--)
                {
                    copy_matrix.subtractRow(k, i, copy_matrix[k][i] / copy_matrix[i][i]);
                }
                break;
            }
        }
    }
    return copy_matrix;
}

Matrix Matrix::additionalMatrix(const Matrix& matrix)
{
    try
    {
        if(matrix.rows != this->rows)
        {
            throw MatrixException("Count of rows doesn't equal in matrices");
        }
        Matrix additional_matrix = Matrix(this->rows, this->cols + matrix.cols);
        for(int i = 0; i < this->rows; i++)
        {
            vector<double> row_vector;
            row_vector.insert(row_vector.end(), this->data[i].begin(), this->data[i].end());
            row_vector.insert(row_vector.end(), matrix.data[i].begin(), matrix.data[i].end());
            additional_matrix.data[i].clear();
            additional_matrix.data[i] = row_vector;
            row_vector.clear();
        }
        return additional_matrix;
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "additionalMatrix");
    }
}


Matrix Matrix::invertibleMatrix()
{
    try
    {
        if(!Matrix::isSquareMatrix(*this))
        {
            throw MatrixException(MatrixException::notSquareMatrix);
        }
        if(this->determineOfMatrix() == 0)
        {
            throw MatrixException("The determine of matrix can't be zero");
        }
        // Make empty single matrix
        DiagMatrix diag_matrix = DiagMatrix(this->rows, 1);
        // Cross over two matrices
        Matrix gen_matrix = this->additionalMatrix(diag_matrix);
        // Right diag form
        Matrix right_tr_mt = gen_matrix.makeRightTriangular();
        // Normalization of diagonal
        for(int i = 0; i < right_tr_mt.rows; i++)
        {
            right_tr_mt.scaleRow(i, 1 / right_tr_mt[i][i]);
        }
        // Left diag form
        Matrix result_mt = right_tr_mt.makeLeftTriangular();
        // Slice
        return result_mt.sliceOfMatrix(0, this->cols);
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "invertibleMatrix");
    } catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "invertibleMatrix");
    }
}

Matrix Matrix::sliceOfMatrix(unsigned row, unsigned col)
{
    try
    {
        if(!Matrix::isCellValid(*this, row, col))
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        Matrix slice_matrix = Matrix(this->rows - row, this->cols - col);
        for(int i = row; i < this->rows; i++)
        {
            vector<double> new_row;
            for(int j = col; j < this->cols; j++)
            {
                new_row.push_back(this->data[i][j]);
            }
            slice_matrix[i - row].clear();
            slice_matrix[i - row] = new_row;
        }
        return slice_matrix;
    } catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "sliceOfMatrix");
    }
}

bool Matrix::isVectorEmpty(const vector<double>& vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if (vec[i] != 0)
        {
            return false;
        }
    }
        return true;
}

unsigned Matrix::rank()
{
    try
    {
        unsigned rank = this->rows;
        Matrix left_mt = this->makeLeftTriangular();
        for(int i = 0; i < this->rows; i++)
            if(Matrix::isVectorEmpty(this->data[i]))
                rank--;
        return rank;
    } catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "rank");
    } catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "rank");
    }
}

Matrix Matrix::transposeMatrix()
{
    Matrix new_matrix = Matrix(this->cols, this->rows);
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            new_matrix[j][i] = this->data[i][j];
    return new_matrix;
}


double Matrix::cos(const Matrix &matrix)
{
    try
    {
        double cos = this->cos(matrix);
        return acos(cos);
    } catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "angle");
    }
}
// NEW
Matrix Matrix::getColumn(unsigned num)
{
    try
    {
        Matrix col_vector = Matrix(this->rows, 1);
        for (int i = 0; i < this->rows; i++) {
            col_vector[i][0] = this->data[i][num];
        }
        return col_vector;
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "getColumn");
    }
}

Matrix Matrix::getRow(unsigned num)
{
    try
    {
        Matrix col_vector = Matrix(1, this->cols);
        for (int i = 0; i < this->cols; i++) {
            col_vector[0][i] = this->data[num][i];
        }
        return col_vector;
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "getRow");
    }
}


void Matrix::fillColumn(const Matrix &other, unsigned num)
{
    try
    {
        if(!Matrix::isVerticalVector(other))
        {
            throw MatrixException(MatrixException::notVector);
        }
        if(other.rows != this->rows)
        {
            throw MatrixException(MatrixException::notEqualMatrices);
        }
        for(unsigned i = 0; i < this->rows; i++)
        {
            this->data[i][num] = other.data[i][0];
        }
    } catch(MatrixException exc)
    {
        throw DefaultClassException("Matrix", "appendColumn");
    }
}

void Matrix::appendRow(const Matrix &other)
{
    try
    {
        if(!Matrix::isVerticalVector(other))
        {
            throw MatrixException(MatrixException::notVector);
        }
        (this->data).push_back(vector<double> {});
        this->rows++;
        for(unsigned i = 0; i < this->cols; i++)
        {
            this->data[this->rows - 1][i] = other.data[0][i];
        }
    } catch(MatrixException exc)
    {
        throw DefaultClassException("Matrix", "appendColumn");
    }
}

double Matrix::colSum(unsigned num)
{
    try
    {
        if(this->cols < num)
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        double sum = 0;
        for (int i = 0; i < this->rows; i++) {
            sum += this->data[i][num];
        }
        return sum;
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "colSum");
    }
}

double Matrix::rowSum(unsigned num)
{
    try
    {
        if(this->rows < num)
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        double sum = 0;
        for (int i = 0; i < this->cols; i++) {
            sum += this->data[num][i];
        }
        return sum;
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "rowSum");
    }
}