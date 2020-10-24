#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string input = argv[1];
    for (int i = 0; i<input.length()/2; i++)
        if (input[i]!=input[input.length()-1-i])
        {
            cout << "NIE";
            return 0;
        }
    cout << "TAK";
    return 0;
}