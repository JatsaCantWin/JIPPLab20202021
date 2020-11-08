#include <iostream>

using namespace std;

void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

int main()
{    
    int a; int b;
    cout << "Kilka testow funckji swap:" << endl;
    a = 5; b = 2;
    swap(a, b);
    cout << a << " " << b << endl;
    a = -500; b = 1;
    swap(a, b);
    cout << a << " " << b << endl;
    a = 1000; b = 0;
    swap(a, b);
    cout << a << " " << b << endl;
    a = -30000; b = 32112323;
    swap(a, b);
    cout << a << " " << b << endl;
    a = -333; b = 333;
    swap(a, b);
    cout << a << " " << b << endl;
    a = -321332; b = 2322;
    swap(a, b);
    cout << a << " " << b << endl;
    a = 0; b = 0;
    swap(a, b);
    cout << a << " " << b << endl;
    a = 22222; b = 0;
    swap(a, b);
    cout << a << " " << b << endl;
    a = 23232; b = 132321;
    swap(a, b);
    cout << a << " " << b << endl;
    a = 2131245; b = -23142141;
    swap(a, b);
    cout << a << " " << b;
    return 0;
}