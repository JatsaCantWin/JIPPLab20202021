#include <iostream>

using namespace std;

int addAndMultiply(int a, int b, int &sum)
{
    sum = a + b;
    return a*b;
}

int main()
{    
    int a;
    int b;
    int sum;
    cout << "Podaj dwie liczby do na ktorych wykonane zostana operacje" << endl;
    cin >> a >> b;
    cout << "Iloczyn obu liczb:" << endl << addAndMultiply(a, b, sum) << endl;
    cout << "Suma obu liczb:" << endl << sum;
    return 0;
}