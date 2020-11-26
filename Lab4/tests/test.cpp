#include <iostream>
#include <matrix/matrix.h>

using namespace std;

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
    D.store("D.txt", ".");
    Matrix E("D.txt", ".");
    E.print();
    return 0;
}
