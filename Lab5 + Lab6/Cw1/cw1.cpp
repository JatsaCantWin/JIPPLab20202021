#include <iostream>
#include <fstream>
#include "sqlite3.h"

using namespace std;

int matrixVal;

static int loadVal(void *NotUsed, int argc, char **argv, char **azColName) {
	matrixVal=atoi(argv[0]);
	return 0;
}

class Matrix
{
    private:
        double *matrixValues;
        int height, width;
    public:
        Matrix(int x, int y);
        Matrix(int x);
        Matrix(string filePath, int matrixID);
        void set(int n, int m, double val);
        double get(int n, int m);
        Matrix add(Matrix m2);
        Matrix subtract(Matrix m2);
        double multiplyRowAndColumn(int n, int m, Matrix m2);
        Matrix multiply(Matrix m2);
        int cols();
        int rows();
        void print();
        void store(char* filePath);
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

Matrix::Matrix(string filePath, int matrixID)
{
	sqlite3 *db;
	sqlite3_open(filePath.c_str(), &db);
	string sql;
	sql = "SELECT Height FROM MatrixSize WHERE ID="+to_string(matrixID);
	sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL);
	height=matrixVal;
	sql = "SELECT Width FROM MatrixSize WHERE ID="+to_string(matrixID);
	width=matrixVal;
	sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL);
	for (int i=0; i<height*width; i++)
	{
		sql = "SELECT Field_Value FROM MatrixFields WHERE ID = "+to_string(matrixID)+" AND Field_ID = "+to_string(i);
		sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL);
		matrixValues[i]=matrixVal;
    }
     sqlite3_close(db);
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

void Matrix::store(char* filePath)
{
	sqlite3 *db;
	sqlite3_open(filePath, &db);
	string sql;
	sql = "INSERT INTO MatrixSize (Height, Width) VALUES ("+to_string(height)+", "+to_string(width)+")";
   	sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
   	sql = "SELECT ID FROM MatrixSize WHERE id=(SELECT max(ID) FROM MatrixSize)";
   	sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL);
    for (int i=0; i<height*width; i++)
    {
		sql = "INSERT INTO MatrixFields VALUES ("+to_string(matrixVal)+", "+to_string(i)+", "+to_string(matrixValues[i])+")";
		sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
    }
     sqlite3_close(db);
}

int main()
{
    cout << "Inicjalizacja macierzy A" << endl;
    Matrix A(4, 5);
    A.set(0, 0, 7); A.set(0, 1, 6); A.set(0, 2, 3); A.set(0, 3, 3); A.set(0, 4, 2);
    A.set(1, 0, 3); A.set(1, 1, 7); A.set(1, 2, 2); A.set(1, 3, 5); A.set(1, 4, 7);
    A.set(2, 0, 2); A.set(2, 1, 2); A.set(2, 2, 1); A.set(2, 3, 1); A.set(2, 4, 1);
    A.set(3, 0, 9); A.set(3, 1, 4); A.set(3, 2, 4); A.set(3, 3, 2); A.set(3, 4, 9);
    A.print();
    cout << "Inicjalizacja macierzy B" << endl;
    Matrix B(4, 5);
    B.set(0, 0, 2); B.set(0, 1, 2); B.set(0, 2, 1); B.set(0, 3, 2); B.set(0, 4, 4);
    B.set(1, 0, 1); B.set(1, 1, 3); B.set(1, 2, 0); B.set(1, 3, 8); B.set(1, 4, 1);
    B.set(2, 0, 6); B.set(2, 1, 4); B.set(2, 2, 5); B.set(2, 3, 3); B.set(2, 4, 6);
    B.set(3, 0, 7); B.set(3, 1, 2); B.set(3, 2, 3); B.set(3, 3, 5); B.set(3, 4, 4);
    B.print();
    cout << "Dodawanie macierzy B do macierzy A:" << endl;
    A.add(B).print();
    cout << "Odejmowanie macierzy B od macierzy A:" << endl;
    A.subtract(B).print();
    cout << "Inicjalizacja macierzy C" << endl;
    Matrix C(5, 4);
    C.set(0, 0, 2); C.set(0, 1, 2); C.set(0, 2, 1); C.set(0, 3, 2);
    C.set(1, 0, 1); C.set(1, 1, 3); C.set(1, 2, 0); C.set(1, 3, 8);
    C.set(2, 0, 6); C.set(2, 1, 4); C.set(2, 2, 5); C.set(2, 3, 3);
    C.set(3, 0, 7); C.set(3, 1, 2); C.set(3, 2, 3); C.set(3, 3, 5);
    C.set(4, 0, 2); C.set(4, 1, 9); C.set(4, 2, 5); C.set(4, 3, 1);
    C.print();
    cout << "Mnozenie macierzy A przez macierz C:" << endl;
    A.multiply(C).print();
    cout << "Liczba kolumn macierzy A:" << endl;
    cout << A.cols() << endl;
    cout << "Liczba wierszy macierzy A:" << endl;
    cout << A.rows() << endl;
    cout << "Inicjalizacja kwadratowej macierzy D" << endl;
    Matrix D(4);
    D.set(0, 0, 1); D.set(0, 1, 6); D.set(0, 2, 4); D.set(0, 3, 4);
    D.set(1, 0, 2); D.set(1, 1, 3); D.set(1, 2, 2); D.set(1, 3, 8);
    D.set(2, 0, 9); D.set(2, 1, 1); D.set(2, 2, 7); D.set(2, 3, 2);
    D.set(3, 0, 3); D.set(3, 1, 2); D.set(3, 2, 1); D.set(3, 3, 3);
    D.print();
    cout << "Zapisywanie macierzy D do pliku i tworzenie nowej macierzy E na jego podstawie:" << endl;
    D.store("matrices.db");
    Matrix E("matrices.db", matrixVal);
	E.print();
    return 0;
}
