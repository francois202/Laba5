#include "MatrixException.h"



MatrixException::MatrixException(string msg): BasicException(std::move(msg)) {};

string MatrixException::limitsViolated = "You are out of bounds of the matrix";
string MatrixException::notDiagonalElement = "You request the cell which can't place into main diagonal";
string MatrixException::notEqualMatrices = "Your matrices are not equal";
string MatrixException::notSquareMatrix = "Doesn't square matrix";
string MatrixException::cannotBeMultiplied = "Matrices cannot be multiplied";
string MatrixException::notTriangularMatrixCell = "This cell doesn't belong to the Triangular matrix";
string MatrixException::notVector = "This matrix should be vector";
string MatrixException::notDoubleValue = "This matrix has a non-double value";
string MatrixException::notCorrectMatrix = "Trying to initialize un-correct matrix";
string MatrixException::emptyMatrix = "Matrix can't be empty";

const char* MatrixException::limitsViolatedErr()
{ return MatrixException::limitsViolated.c_str(); }

const char* MatrixException::notDiagonalElementErr()
{ return MatrixException::notDiagonalElement.c_str(); }

const char* MatrixException::notEqualMatricesErr()
{ return MatrixException::notEqualMatrices.c_str(); }

const char* MatrixException::notSquareMatrixErr()
{ return MatrixException::notSquareMatrix.c_str(); }

const char* MatrixException::cannotBeMultipliedErr()
{ return MatrixException::cannotBeMultiplied.c_str(); }

const char* MatrixException::notTriangularMatrixCellErr()
{ return MatrixException::notTriangularMatrixCell.c_str(); }

const char* MatrixException::notVectorErr()
{ return MatrixException::notVector.c_str();}

const char* MatrixException::notDoubleValueErr()
{ return MatrixException::notDoubleValue.c_str();}

const char* MatrixException::notCorrectMatrixErr()
{ return MatrixException::notCorrectMatrix.c_str();}

const char* MatrixException::emptyMatrixErr()
{ return MatrixException::emptyMatrix.c_str();}