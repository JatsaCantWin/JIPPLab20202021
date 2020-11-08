#include <iostream>

using namespace std;

void swapIfBLower(int *a, int *b)
{
    if (*b<*a)
    {
        *a = *a + *b;
        *b = *a - *b;
        *a = *a - *b;
    }
}

int main()
{    
    int a;
    int b;
    cout << "Podaj dwie liczby do zamienienia miejscami" << endl;
    cin >> a >> b;
    swapIfBLower(&a, &b);
    cout << a << " " << b;
    return 0;
}