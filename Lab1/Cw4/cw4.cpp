#include <iostream>
#include <math.h>

using namespace std;

bool numbersAreSimmilar(int a, int b)
{
    int sumA = 0, sumB = 0;

    for (int i = 1; i<=sqrt(a); i++) 
    {
        if (a%i == 0)
        {
            if (a/i == i) 
                sumA += i;
            else
            {
                sumA += i;
                sumA += a/i;
            }
        }
    }
    sumA-=a;
    for (int i = 1; i<=sqrt(b); i++) 
    {
        if (b%i == 0) 
        {
            if (b/i == i) 
                sumB += i;
            else
            {
                sumB += i;
                sumB += b/i;
            }
        }
    }
    sumB-=b;

    if ((sumA-1==b)&&(sumB-1==a))
        return true;
    else
        return false;
    
}

int main(int argc, char *argv[])
{
    int a, b;

    cout << "Podaj liczby a i b" << endl;
    cin >> a >> b;
    if (numbersAreSimmilar(a, b))
        cout << "Liczby sa skojarzone";
    else
        cout << "Liczby nie sa skojarzone";
    
    return 0;
}