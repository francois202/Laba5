#ifndef MATRIX_FILE
#define MATRIX_FILE

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "helpers.h"
#include <vector>
#include "exceptions/DefaultClassException.h"
#include "exceptions/MatrixException.h"

using namespace std;



class Matrix {
public:

    // Store the Matrix values
    vector<vector<double>> data;

    // Basic constructor
    Matrix(unsigned rows, unsigned cols);

    // Empty matrix
    Matrix();

    // Initialize be vectors
    Matrix(vector<vector<double>> matrix_data);

    // Copy constructor
    Matrix(Matrix* matrix);

    // Destructor
    ~Matrix();

    void clear();

    void fill_matrix(vector<vector<double>> matrix_data);

    // Can be overwritten on child classes
    virtual void set(unsigned row, unsigned col, double value);
    virtual double get(unsigned row, unsigned col);


    // Valid methods
    static bool isCellValid(const Matrix& matrix, unsigned row, unsigned col)
    { return isColValid(matrix, col) && isRowValid(matrix, row); }

    static bool isRowValid(const Matrix& matrix, unsigned row)
    { return row < matrix.rows; }

    static bool isColValid(const Matrix& matrix, unsigned col)
    { return col < matrix.cols; }

    static bool isEqualDimension(const Matrix& matrix1, const Matrix& matrix2)
    { return (matrix1.rows == matrix2.rows) and (matrix1.cols == matrix2.cols); }

    static bool canBeMultiple(const Matrix& matrix1, const Matrix& matrix2)
    { return matrix1.cols == matrix2.rows; }

    static bool isSquareMatrix(const Matrix& matrix)
    { return matrix.rows == matrix.cols; }

    static bool isVector(const Matrix& matrix)
    { return matrix.rows == 1 or matrix.cols == 1; }

    static bool isVerticalVector(const Matrix& matrix)
    { return matrix.cols == 1; }

    static bool isHorizontalVector(const Matrix& matrix)
    { return matrix.rows == 1; }


    // Examples of matrices
    static Matrix testMatrix(int rows, int cols);
    static Matrix testVector(unsigned dim, bool isVertical = true);
    static Matrix testVerticalVector(unsigned rows);
    static Matrix testHorizontalVector(unsigned cols);
    /**
     * Method which make union of +/- operations:
     * @param matrix1
     * @param matrix2
     * @param op_type 1 correspond to '+', 0 correspond to '-'
     * @return
     */
    Matrix groupOperation(const Matrix& matrix1, const Matrix& matrix2, bool op_type = true);

    // Math operations by matrices
    Matrix operator+(const Matrix& matrix);
    Matrix operator-(const Matrix& matrix);
    Matrix operator*(double scale);
    Matrix operator/(double scale);
    Matrix operator*=(double scale);
    Matrix operator/=(double scale);
    Matrix operator*(const Matrix& matrix);
    Matrix hadamardProduct(const Matrix& matrix);
    vector<double>& operator[](int index);

    // Basic matrix operations
    double trace();
    // Multiple of items of main diagonal
    double productTrace();

    void replaceRows(unsigned first_row, unsigned second_row);
    void scaleRow(unsigned row, double scale);
    Matrix makeLeftTriangular();
    Matrix makeRightTriangular();
    Matrix sliceOfMatrix(unsigned row, unsigned col);
    Matrix invertibleMatrix();
    Matrix additionalMatrix(const Matrix& matrix);
    Matrix transposeMatrix();
    void subtractRow(unsigned from, unsigned which, double scale);
    double rowSum(unsigned num);
    double colSum(unsigned num);
    double determineOfMatrix();
    unsigned rank();

    // Basic vectors operations
    double scalarProduct(const Matrix& matrix);
    double cos(const Matrix& matrix);
    double maxValueOfVector();
    double EuclideanNorm() const;
    double ChebishevNorm();
    double FrobeniousNorm();
    bool static isVectorEmpty(const vector<double>& vec);

    // Get submatrix
    Matrix getColumn(unsigned num);
    Matrix getRow(unsigned num);

    // Matrix manipulations
    void appendRow(const Matrix& other);
    void fillColumn(const Matrix& other, unsigned num);

    /*
     * Define friendly function of an operator overloading with help of template
    */
    friend ostream& operator<<(ostream& stream, const Matrix& matrix);
    friend ofstream& operator<<(ofstream& stream, const Matrix& matrix);

    unsigned rows = 0;
    unsigned cols = 0;
};


/**
 *
 * @param stream
 * @param matrix
 * @return
 */
inline ostream& operator<<(ostream& stream, const Matrix& matrix)
{
    vector<vector<double>> m_data = matrix.data;
    for(auto & row : m_data)
    {
        for(auto & col : row)
            stream << col << " ";
        stream << "\n";
    }
    return stream;
}

inline ifstream& operator>>(ifstream& stream, Matrix& matrix)
{
    vector<vector<double>> matrix_data;
    string line;
    try {

        while(getline(stream, line))
        {

            vector<double> row;
            string delimiter = "\t";
            string token;
            size_t pos = 0;
            while((pos = line.find(delimiter)) != string::npos)
            {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                if (!is_double(token.c_str()))
                {
                    throw MatrixException(MatrixException::notDoubleValue);
                }
                row.push_back(str_to_double(token.c_str()));
            }
            row.push_back(str_to_double(line.substr(0, pos).c_str()));
            matrix_data.push_back(row);
        }
        matrix.fill_matrix(matrix_data);
        return stream;
    }
    catch (DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "fstream_operator>>");
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("Matrix", "fstream_operator>>");
    }
}

inline ofstream& operator<<(ofstream& stream, const Matrix& matrix)
{
    vector<vector<double>> matrix_data = matrix.data;
    for(auto & row : matrix_data)
    {
        string row_string;
        for(auto & col : row)
        {
            row_string += tostring(col) + "\t";
        }
        row_string.pop_back();
    }
    return stream;
}
#endif