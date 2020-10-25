#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int matA[2][3], matB[2][3], matR[2][3];

    cout << "Podaj obie macierze wierszami" << endl;
    for (int i=0; i<2; i++)
        for (int j=0; j<3; j++)
            cin >> matA[i][j];
    for (int i=0; i<2; i++)
        for (int j=0; j<3; j++)
        {
            cin >> matB[i][j];
            matR[i][j]=matA[i][j]+matB[i][j];
        }
    cout << "Wynik:" << endl;
    for (int i=0; i<2; i++)
    {
        for (int j=0; j<3; j++)
            cout << matR[i][j] << " ";
        cout << endl;
    }
    return 0;
}