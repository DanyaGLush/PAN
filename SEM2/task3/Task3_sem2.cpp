

#include <iostream>
#include <cmath>

using namespace std;

double calculateA(double T, double D, double M) {
    double a;
    a = (T - D) / M;
    return a;
}

double calculateAY(double L, double M) {
    double ay;
    ay = (L - M * 9.8) / M;
    return ay;
}

int main()
{
    double M, L, D, T, a,ay;
    cout << "Масса самолета: ";
    cin >> M;
    cout << "Подъемная сила: ";
    cin >> L;
    cout << "Сопротивление: ";
    cin >> D;
    cout << "Тяга: ";
    cin >> T;
    cout << "Ускорение по направлению движения: " << calculateA(T, D, M) << endl;
    cout << "Вертикальное ускорение: " << calculateAY(L, M);

}

