#include <iostream>
#include <fstream>

using namespace std;

class Matrix
{
    private:
        double *matrixValues;
        int height, width;
    public:
        Matrix(int x, int y);
        Matrix(int x);
        Matrix(string filename, string path);
        void set(int n, int m, double val);
        double get(int n, int m);
        Matrix add(Matrix m2);
        Matrix subtract(Matrix m2);
        double multiplyRowAndColumn(int n, int m, Matrix m2);
        Matrix multiply(Matrix m2);
        int cols();
        int rows();
        void print();
        void store(string filename, string path);
};

Matrix::Matrix(int x, int y)
{
    matrixValues = new double[x*y*sizeof(double)];
    height = x; width = y;
    for (int i=0; i<x*y; i++)
        matrixValues[i]=0;
}

Matrix::Matrix(int x)
{
    matrixValues = new double[x*x*sizeof(double)];
    height = x; width = x;
    for (int i=0; i<x*x; i++)
        matrixValues[i]=0;
}

Matrix::Matrix(string filename, string path)
{
    ifstream matrixFile;

    path = path + "/" + filename;
    matrixFile.open(path.c_str());
    matrixFile >> height >> width;
    matrixValues = new double[height*width*sizeof(double)];
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            matrixFile >> matrixValues[i*width+j];
}

void Matrix::set(int n, int m, double val)
{
    matrixValues[n*width+m] = val;
}

double Matrix::get(int n, int m)
{
    return matrixValues[n*width+m];
}

Matrix Matrix::add(Matrix m2)
{
    Matrix result(height, width);
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            result.set(i, j, get(i, j)+m2.get(i, j));
    return result;
}

Matrix Matrix::subtract(Matrix m2)
{
    Matrix result(height, width);
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            result.set(i, j, get(i, j)-m2.get(i, j));
    return result;
}

double Matrix::multiplyRowAndColumn(int n, int m, Matrix m2)
{
    double result = 0;
    for (int i=0; i<width; i++)
        result+= get(n, i)*m2.get(i, m);
    return result;
}

Matrix Matrix::multiply(Matrix m2)
{
    Matrix result(m2.width, height);
    for (int i=0; i<result.height; i++)
        for (int j=0; j<result.width; j++)
            result.set(i, j, multiplyRowAndColumn(i, j, m2));
    return result;
}

int Matrix::cols()
{
    return width;
}

int Matrix::rows()
{
    return height;
}

void Matrix::print()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
            cout << get(i, j) << " ";
        cout << endl;
    }
}

void Matrix::store(string filename, string path)
{
    ofstream matrixFile;

    path = path + "/" + filename;
    matrixFile.open(path.c_str());
    matrixFile << rows() << " " << cols() << endl;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
            matrixFile << get(i, j) << " ";
        matrixFile << endl;
    }
    matrixFile.close();
}