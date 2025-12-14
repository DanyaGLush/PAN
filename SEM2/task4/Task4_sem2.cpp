
#include <cmath>
#include <iostream>
//#include <limits>

using namespace std;

double inputpar() {
    double value;
    while (!(cin >> value) || value <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

double calculate_t(double a, double h) {
    double t;
    t = pow(2 * h / a, 0.5);
    return(t);
}

int main()
{
	double a, h;
    cout << "Введите значение ускорения: ";
    a = inputpar();
    cout << "Введите значение высоты: ";
    h = inputpar();
    cout << "Время для набора заданной высоты: " << calculate_t(a,h) << "c";

}

