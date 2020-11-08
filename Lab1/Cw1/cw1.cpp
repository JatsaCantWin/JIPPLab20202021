#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int cmpfunc (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[])
{
    int input[argc-1];
    for (int i = 0; i< argc-1; i++)
        input[i] = stoi(argv[i+1]);

    qsort(input, argc-1, sizeof(int), cmpfunc);

    cout << "out = ";

    for (int i = 0; i < argc-1; i++)
        cout << (int)input[i] << " ";

    return 0;
}