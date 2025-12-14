

#include <iostream>
#include <cmath> 


using namespace std;

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
    L = 0.5 * p * S * C * pow(V,2);
    cout << "Подъемная сила: " << L << endl;
    
}

