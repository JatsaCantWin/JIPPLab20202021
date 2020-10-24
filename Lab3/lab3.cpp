#include <iostream>

using namespace std;

int main() 
{
    double weight, height;
    double BMI;

    cout << "Podaj wzrost [m]:" << endl;
    cin >> height;
    cout << "Podaj wage [kg]:" << endl;
    cin >> weight;
    BMI = weight/(height*height);

    if (BMI < 16) {
        cout << BMI << " - wyglodzenie";
    } else if (BMI < 17) {
        cout << BMI << " - wychudzenie";
    } else if (BMI < 18.5) {
        cout << BMI << " - niedowaga";
    } else if (BMI < 25) {
        cout << BMI << " - wartosc prawidlowa";
    } else if (BMI < 30) {
        cout << BMI << " - nadwaga";
    } else if (BMI < 35) {
        cout << BMI << " - I stopien otylosci";
    } else if (BMI < 40) {
        cout << BMI << " - II stopien otylosci";
    } else {
        cout << BMI << " - otylosc skrajna";
    }
}