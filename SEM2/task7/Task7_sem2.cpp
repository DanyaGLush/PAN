

#include <iostream>
#include<cmath>

using namespace std;

//Корректность введенных значений
double inputpar() {
    double value;
    while (!(cin >> value) || value <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

double calculate_a(double m, double t, double d) {
    double a;
    a = (t - d) / m;
    return a;
}

double calculate_ay(double l, double m, double g) {
    double ay;
    ay = (l - m*g) / m;
    return ay;
}

int main()
{
    const double g = 9.8;
    double t, l, d, m, ay;
    cout << "Введите массу самолета: ";
    m = inputpar();
    cout << "Введите значение тяги: ";
    t = inputpar();
    cout << "Введите значение подъемной силы: ";
    l = inputpar();
    cout << "Введите значение сопротивления: ";
    d = inputpar();
    cout << "Введенные данные: " << "M = " << m << " T = " << t << " L = " << l << " D = " << d << endl;
    cout << "Ускорение по направлению движения: " << calculate_a(m, t, d) << endl;
    ay = calculate_ay(l, m, g);
    cout << "Вертикальное ускорение: " << ay << endl;
    if (ay > 0.5)
        cout << "Режим \"набор высоты\"";
    else if (ay < 0)
        cout << "Режим \"снижение\"";
    else
        cout << "Режим \"горизонтальный полет\"";
}
