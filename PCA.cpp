#include "PCA.h"
#include "cmath"
#include <vector>
#include <string>
#include <map>


void PCA::scaling()
{
    for(int i = 0; i < this->cols; i++)
    {
        double col_average = this->colSum(i) / this->rows;
        double col_std = this->colStd(i);
        for(int j = 0; j < this->rows; j++)
        {
            this->data[j][i] -= col_average;
            this->data[j][i] /= col_std;
        }
    }
}

double PCA::colStd(unsigned num)
{
    try
    {
        if((this->cols < num))
        {
            throw MatrixException(MatrixException::limitsViolated);
        }
        if(this->rows == 0)
        {
            throw MatrixException(MatrixException::notCorrectMatrix);
        }
        double col_average = this->colSum(num) / this->rows;
        double median_sum = 0;
        for (int i = 0; i < this->rows; i++)
        {
            median_sum += pow(this->data[i][num] - col_average, 2);
        }
        return sqrt(median_sum / (this->rows));
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "colStd");
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "colStd");
    }
}

void PCA::operator-=(const Matrix &matrix)
{
    try
    {
        if(!Matrix::isEqualDimension(this, matrix))
        {
            throw MatrixException(MatrixException::notEqualMatrices);
        }
        for(int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->data[i][j] -= matrix.data[i][j];
            }
        }
    }
    catch (MatrixException exc)
    {
        throw DefaultClassException("PCA", "operator-=");
    }
}

map<string, Matrix> PCA::NEPAL()
{
    try
    {
        PCA E = PCA(this);
        unsigned cp = (E.rows > E.cols) ? E.cols : E.rows;
        Matrix P = Matrix(this->cols, 12);
        Matrix T = Matrix(this->rows, 12);
        double eps = 0.0000001;
        for (unsigned h = 0; h < cp; h++)
        {
            Matrix t = E.getColumn(h);
            Matrix d = Matrix(E.rows, 1);
            Matrix p = Matrix(E.cols, 1);
            do {
                p = ((t.transposeMatrix() * E) / t.EuclideanNorm()).transposeMatrix();
                p /= p.EuclideanNorm();
                Matrix t_old = Matrix(t);
                t = (E * p) / p.EuclideanNorm();
                d = t_old - t;
            } while (d.EuclideanNorm() > eps);

            E -= t * p.transposeMatrix();
            P.fillColumn(p, h);
            T.fillColumn(t, h);
        }
        return map<string, Matrix>{{"E", E}, {"P", P}, {"T", T}};
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "NEPAL");
    }

}

Matrix PCA::range(Matrix T_matrix)
{
    try
    {
        Matrix mahal_middle = (T_matrix.transposeMatrix() * T_matrix).invertibleMatrix();
        vector<double> coffs;
        for (unsigned i = 0; i < T_matrix.rows; i++) {
            Matrix col = T_matrix.getRow(i);
            double h = (col * mahal_middle * col.transposeMatrix()).data[0][0];
            coffs.push_back(h);
        }
        vector<vector<double>> range_vector;
        range_vector.push_back(coffs);

        Matrix res_matrix = Matrix(range_vector);
        return res_matrix;
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "range");
    }
}

Matrix PCA::remainders(Matrix E_matrix)
{
    try
    {
        vector<double> remainders;
        for (unsigned i = 0; i < E_matrix.cols; i++) {
            Matrix row = E_matrix.getRow(i);
            remainders.push_back(row.EuclideanNorm());
        }
        vector<vector<double>> remainder_vector;
        remainder_vector.push_back(remainders);
        Matrix res_matrix = Matrix(remainder_vector);
        return res_matrix;
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "remainders");
    }
}

double PCA::TRV(Matrix remainders, map<string, unsigned> size)
{
    try
    {
        if(!(size["rows"] and size["cols"]))
        {
            throw MatrixException("Rows and cols can't be null");
        }
        return remainders.rowSum(0) / (size["rows"] * size["cols"]);
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "TRV");
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "TRV");
    }
}

double PCA::ERV(map<string, Matrix> nepals)
{
    try
    {
        double val_sum = pow(this->FrobeniousNorm(), 2);
        if(val_sum == 0)
        {
            throw MatrixException("Something went wrong. Doesn't correct matrix's coeffs");
        }
        Matrix remainder_matrix = PCA::remainders(nepals.at("E"));
        return 1.0 - remainder_matrix.rowSum(0) / val_sum;
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "ERV");
    }
    catch(MatrixException exc)
    {
        cout << exc.getError() << endl;
        throw DefaultClassException("PCA", "ERV");
    }
    catch(exception exc)
    {
        cout << "Map of NEPAL's executing hasn't key E" << endl;
        throw DefaultClassException("PCA", "ERV");
    }
}