#include "tests.h"

void test_basic_matrix()
{
    try
    {
        Matrix mt = Matrix(2, 3);
        mt.set(1, 2, 1.4);
        mt.set(0, 1, 1.5);
        cout << "Representation of the basic matrix: (2x3)" << endl;
        cout << mt;
        cout << "Getting of the cell: (1, 2): " << endl;
        cout << mt.get(0, 1) << endl;

        Matrix mt1 = Matrix::testMatrix(2, 3);
        Matrix mt2 = Matrix::testMatrix(2, 3);
        cout << "Two test matrices: " << endl;
        cout << mt1 << mt2 << endl;

        cout << "Sum of two matrices: " << endl;
        cout << mt1 + mt2 << endl;

        cout << "Difference of two matrices: " << endl;
        cout << mt1 - mt << endl;

        cout << "Product of the matrix by a scalar: " << endl;
        cout << mt * 2.3 << endl;

        cout << "Hadamard product of two matrices: " << endl;
        cout << mt.hadamardProduct(mt1) << endl;

        cout << "Cell by index of the matrix: (2, 2)" << endl;
        cout << mt[1][1] << endl;
    }
    catch(DefaultClassException exception)
    {
        cout << exception.getError() << endl;
    }
}

void test_triangular_matrix()
{
    try
    {
        TriangularMatrix tr_mt = TriangularMatrix::testMatrix(3);
        cout << "Example of the triangular matrix: " << endl;
        cout << tr_mt << endl;
    } catch(DefaultClassException exception)
    {
        cout << exception.getError() << endl;
    }
}

void test_single_matrix()
{
    try
    {
        SingleMatrix s_mt = SingleMatrix(3, 4);
        cout << "Generate of the single matrix of 3 dimension by 4 value: " << endl;
        cout << s_mt << endl;
    } catch(DefaultClassException exception) {
        cout << exception.getError() << endl;
    }
}


void test_diagonal_matrix()
{
    try
    {
        DiagMatrix d_mt = DiagMatrix(3, 5);
        cout << "Generation of the diagonal matrix of 4 dimension by 1.5 value: " << endl;
        cout << d_mt << endl;
    } catch(DefaultClassException exception)
    {
        cout << exception.getError() << endl;
    }
}

void test_vector_methods()
{
    try {
        Matrix v1 = Matrix::testHorizontalVector(5);
        Matrix v2 = Matrix::testVerticalVector(5);
        cout << "Horizontal vector: " << endl;
        cout << v1 << endl;
        cout << "Vertical vector: " << endl;
        cout << v2 << endl;
        cout << "Scalar product: " << endl << v1.scalarProduct(v2) << endl;
        cout << "Euclidean norm of horizontal vector: " << endl << v1.EuclideanNorm() << endl;
        cout << "Euclidean norm of vertical vector: " << endl << v2.EuclideanNorm() << endl;
        cout << "Chebishev norm of vertical vector: " << endl << v2.ChebishevNorm() << endl;
        Matrix vt_1 = Matrix(1, 2);
        Matrix vt_2 = Matrix(2, 1);
        vt_1[0][0] = 1;
        vt_1[0][1] = 1;
        vt_2[0][0] = 1;
        vt_2[1][0] = -1;
        cout << "Cos: " << vt_1.cos(vt_2) << endl;
    }
    catch(DefaultClassException exception)
    {
        cout << exception.getError() << endl;
    }
}

void test_matrices_methods()
{
    Matrix mt = Matrix(3, 3);
    mt[0][0] = 0;
    mt[0][1] = -3;
    mt[0][2] = 5;
    mt[1][0] = 1;
    mt[1][1] = 0;
    mt[1][2] = -4;
    mt[2][0] = 2;
    mt[2][1] = 1;
    mt[2][2] = -1;
    Matrix mt_test = Matrix::testMatrix(2, 3);
    cout << mt_test.transposeMatrix() << endl;
    cout << "Original matrix: " << endl;
    cout << mt << endl;
    cout << "Invertible matrix: " << endl;
    cout << mt.invertibleMatrix() << endl;
    cout << "Check of invertible: " << endl;
    cout << mt * mt.invertibleMatrix() << endl;
    cout << "Transpose matrix: " << endl;
    cout << mt.transposeMatrix() << endl;
    cout << "Rank of matrix: " << mt.rank() << endl;
    cout << "Determine of matrix: " << mt.determineOfMatrix() << endl;
    cout << "Matrix norm: " << mt.FrobeniousNorm() << endl;
    cout << "Matrix trace: " << mt.trace() << endl;
    cout << "Frobenious norm: " << mt.FrobeniousNorm() << endl;
}


void test_matrices_read()
{
    try
    {
        string path = "data/new.txt";
        ifstream out(path);
        if (out.is_open())
        {
            Matrix mt_test;
            out >> mt_test;
            cout << mt_test * 10;
        }
        out.close();
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
    }
}

void test_pca()
{
    try
    {
        string path = "D:/D/Clion++/data/data.txt";
        PCA mt_test = PCA();
        ifstream out(path);
        if (out.is_open())
        {
            out >> mt_test;
        }
        out.close();
        cout << "Our matrix:" << endl;
        cout << mt_test;
        mt_test.scaling();
        cout << "Our matrix X:" << endl;
        cout << mt_test;
        map<string, Matrix> result = mt_test.NEPAL();
        cout << endl << "P matrix:" << endl;
        cout << result["P"];
        cout << endl << "T matrix:" << endl;
        cout << result["T"];
        cout << endl << "Error matrix:" << endl;
        cout << result["E"];
        cout << endl << "Correct test: " << endl;
        Matrix test_decomposition = result["T"] * result["P"].transposeMatrix() + result["E"];
        cout << test_decomposition;
        cout << endl << "Ranges: " << endl;
        Matrix range_matrix = PCA::range(result["T"]);
        cout << range_matrix;
        cout << endl << "Range's sum: " << endl;
        cout << range_matrix.rowSum(0) << endl;
        cout << endl << "Remainders: " << endl;
        Matrix remainder_matrix = PCA::remainders(result["E"]);
        cout << remainder_matrix;
        cout << endl << "TRV: ";
        map<string, unsigned> size = {{"rows", mt_test.rows},
                                      {"cols", mt_test.cols}};
        cout << PCA::TRV(remainder_matrix, size);
        cout << endl << "ERV: ";
        cout << mt_test.ERV(result);
    }
    catch(DefaultClassException exc)
    {
        cout << exc.getError() << endl;
    }
}

void test_matrix_write()
{
    string path = "D:/D/Clion++/data/news.txt";
    ofstream in;
    in.open(path, ofstream::out | ofstream::trunc);
    if(in.is_open())
    {
        Matrix mt_text = Matrix::testMatrix(10, 20);
        cout << mt_text;
        in << mt_text;
    }
}


void test()
{
    char type;
    cout << "Choose the type of test: " << endl;
    for(auto const &test_type : test_types)
    {
        cout << test_type << endl;
    }
    bool can_leave = false;
    while(cin.get(type) and !can_leave)
    {
        switch (type)
        {
            case '1':
                can_leave = true;
                test_basic_matrix();
                break;
            case '2':
                can_leave = true;
                test_single_matrix();
                break;
            case '3':
                can_leave = true;
                test_diagonal_matrix();
                break;
            case '4':
                can_leave = true;
                test_triangular_matrix();
                break;
            case '5':
                can_leave = true;
                test_vector_methods();
                break;
            case '6':
                can_leave = true;
                test_matrices_methods();
                break;
            case '7':
                can_leave = true;
                test_matrices_read();
                break;
            case '8':
                can_leave = true;
                test_matrix_write();
                break;
            case '9':
                can_leave = true;
                test_pca();
                break;
            default:
                cout << "Doesn't right input. Repeat your attempt" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}


