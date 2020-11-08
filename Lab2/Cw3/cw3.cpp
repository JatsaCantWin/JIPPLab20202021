#include <iostream>

using namespace std;

void swapReferenceAndPointer(int &a, int *b)
{
    a = a + *b;
    *b = a - *b;
    a = a - *b;
}

int main()
{    
    int a;
    int b;
    cout << "Podaj dwie liczby do zamienienia miejscami" << endl;
    cin >> a >> b;
    swapReferenceAndPointer(a, &b);
    cout << a << " " << b;
    return 0;
}