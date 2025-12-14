

#include <iostream>
#include <cmath>

using namespace std;

double calculateL(double S, double p, double C, double V) {
    return 0.5 * p * S * C * pow(V, 2);
}

int main()
{
    double S, V, p, C, L;
    cout << "Площадь крыла: ";
    cin >> S;
    cout << "Скорость полета: ";
    cin >> V;
    cout << "Плотность воздуха: ";
    cin >> p;
    cout << "Коэффициент подъемной силы: ";
    cin >> C;
    L = calculateL(S, p, C, V);
    cout << "Подъемная сила: " << L << endl;
}

