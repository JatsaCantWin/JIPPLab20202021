#include <iostream>
#include <fstream>
#include "sqlite3.h"

using namespace std;

int matrixVal;

static int loadVal(void *NotUsed, int argc, char **argv, char **azColName) 
{
	try
	{
		matrixVal=atoi(argv[0]);
		if ((argv[0][0]!='0')&&(matrixVal==0))
			throw "Blad konwersji danych przy wyciagniu ich z bazy";
		return 0;	
	}
	catch (const char* err)
	{
		cout << err << endl;
		return -1;
	}
	catch (...)
	{
		cout << "Nie udalo sie wyciagnac danej z bazy" << endl;
		return -1;
	}
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
    try
    {
    	matrixValues = new double[x*y*sizeof(double)];
    	if (matrixValues == NULL)
			throw "Nie udalo sie zarezerwowac pamieci dla wartosci macierzy";
    	height = x; width = y;
    	for (int i=0; i<x*y; i++)
	    	matrixValues[i]=0;	
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "Nie udalo sie utworzyc macierzy" << endl;
	}
}

Matrix::Matrix(int x)
{
	try 
	{
		matrixValues = new double[x*x*sizeof(double)];
  		if (matrixValues == NULL)
  			throw "Nie udalo sie zarezerwowac pamieci dla wartosci macierzy";
		height = x; width = x;
    	for (int i=0; i<x*x; i++)
        	matrixValues[i]=0;	
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "Nie udalo sie utworzyc macierzy" << endl;
	}
}

Matrix::Matrix(string filePath, int matrixID)
{
	try
	{
		sqlite3 *db;
		sqlite3_open(filePath.c_str(), &db);
		if (db == NULL)
			throw "Nie udalo sie otworzyc bazy danych";
		string sql;
		sql = "SELECT Height FROM MatrixSize WHERE ID="+to_string(matrixID);
		if (sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL)!=0)
			throw "Nie udalo sie wykonac polecenia SQL";
		height=matrixVal;
		sql = "SELECT Width FROM MatrixSize WHERE ID="+to_string(matrixID);
		width=matrixVal;
		if (sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL)!=0)
			throw "Nie udalo sie wykonac polecenia SQL";
		for (int i=0; i<height*width; i++)
		{
			sql = "SELECT Field_Value FROM MatrixFields WHERE ID = "+to_string(matrixID)+" AND Field_ID = "+to_string(i);
			if (sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL)!=0)
				throw "Nie udalo sie wykonac polecenia SQL";
			matrixValues[i]=matrixVal;
	    }
	    sqlite3_close(db);	
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "Nie udalo sie utworzyc macierzy" << endl;
	}
}

void Matrix::set(int n, int m, double val)
{
	try
	{
		matrixValues[n*width+m] = val;	
	}
	catch (...)
	{
		cout << "Nie udalo sie ustawic wartosci w macierzy" << endl;
	}
}

double Matrix::get(int n, int m)
{
	try
	{
		return matrixValues[n*width+m];	
	}
	catch (...)
	{
		cout << "Nie udalo sie wyciagnac wartosci z macierzy" << endl;
	}
}

Matrix Matrix::add(Matrix m2)
{
	try
	{
		Matrix result(height, width);
	    for (int i=0; i<height; i++)
	        for (int j=0; j<width; j++)
	            result.set(i, j, get(i, j)+m2.get(i, j));
	    return result;
	}
    catch (...)
	{
		cout << "Nie udalo sie dodac dwoch macierzy" << endl;
		return NULL;
	}
}

Matrix Matrix::subtract(Matrix m2)
{
	try
	{
		Matrix result(height, width);
	    for (int i=0; i<height; i++)
	        for (int j=0; j<width; j++)
	            result.set(i, j, get(i, j)-m2.get(i, j));
	    return result;	
	}
    catch (...)
	{
		cout << "Nie udalo sie odjac dwoch macierzy" << endl;
		return NULL;
	}
}

double Matrix::multiplyRowAndColumn(int n, int m, Matrix m2)
{
	try
	{
		double result = 0;
	    for (int i=0; i<width; i++)
	        result+= get(n, i)*m2.get(i, m);
	    return result;	
	}
    catch (...)
	{
		cout << "Nie udalo sie przemnozyc kolumny jednej macierzy przez rzad drugiej" << endl;
		return 0;
	}
}

Matrix Matrix::multiply(Matrix m2)
{
	try
	{
		Matrix result(m2.width, height);
	    for (int i=0; i<result.height; i++)
	        for (int j=0; j<result.width; j++)
	            result.set(i, j, multiplyRowAndColumn(i, j, m2));
	    return result;	
	}
	catch (...)
	{
		cout << "Nie udalo sie przemnozyc dwoch macierzy" << endl;
		return NULL;
	}
}

int Matrix::cols()
{
	try
	{
		return width;
	}
	catch (...)
	{
		cout << "Nie udalo sie uzyskac liczby kolumn macierzy" << endl;
		return -1;
	}
}

int Matrix::rows()
{
	try
	{
		return height;	
	}
	catch (...)
	{
		cout << "Nie udalo sie uzyskac liczby wierszy macierzy" << endl;
		return -1;
	}
}

void Matrix::print()
{
	try
	{
		for (int i=0; i<height; i++)
	    {
	        for (int j=0; j<width; j++)
	            cout << get(i, j) << " ";
	        cout << endl;
	    }	
	}
	catch (...)
	{
		cout << "Nie udalo sie wypisac wartosci macierzy" << endl;
	}
}

void Matrix::store(char* filePath)
{
	try
	{
		sqlite3 *db;
		sqlite3_open(filePath, &db);
		if (db == NULL)
			throw "Nie udalo sie otworzyc bazy danych";
		string sql;
		sql = "INSERT INTO MatrixSize (Height, Width) VALUES ("+to_string(height)+", "+to_string(width)+")";
	   	if (sqlite3_exec(db, sql.c_str(), NULL, 0, NULL)!=0)
	   		throw "Nie udalo sie wykonac polecenia SQL";
	   	sql = "SELECT ID FROM MatrixSize WHERE id=(SELECT max(ID) FROM MatrixSize)";
	   	if (sqlite3_exec(db, sql.c_str(), loadVal, 0, NULL)!=0)
	   		throw "Nie udalo sie wykonac polecenia SQL";
	    for (int i=0; i<height*width; i++)
	    {
			sql = "INSERT INTO MatrixFields VALUES ("+to_string(matrixVal)+", "+to_string(i)+", "+to_string(matrixValues[i])+")";
			if (sqlite3_exec(db, sql.c_str(), NULL, 0, NULL)!=0)
				throw "Nie udalo sie wykonac polecenia SQL";
	    }
	    sqlite3_close(db);	
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "Nie udalo sie przechowac macierzy w bazie danych" << endl;
	}
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
