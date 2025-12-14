

#include <iostream>
#include <cmath>]

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

double calculate_L1(double V, double P, double coef_Cl, double square) {
    double L;
    L = 0.5 * P * pow(V,2) * coef_Cl * square;
    return(L);
}

double calculate_L2(double V, double P, double coef_Cd, double square) {
    double L;
    L = 0.5 * P * pow(V,2) * coef_Cd * square;
    return(L);
}

double calculate_min(double mas[]) {
    double min = mas[0];
    int index = 1;
    for (int i = 1; i < 3; i++)
        if (mas[i] < min)
            index = i+1;
    return(index);
}



int main()
{
    const int size = 3;
    const double g = 9.8;
    // общие данные:
    double V, P;
    cout << "Введите скорость полета: ";
    V = inputpar();
    cout << "Введите значение плотности воздуха: ";
    P = inputpar();
    // Заполнение характеристки самолетов:
    double weight[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите массу " << i+1 << "-го самолета: ";
        weight[i] = inputpar();
    }
   
    double square[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите площадь крыла " << i+1 << "-го самолета: ";
        square[i] = inputpar();
    }
   
    double thrust[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите тягу " << i+1 << "-го самолета: ";
        thrust[i] = inputpar();
    }

    double coef_Cd[size];
    double coef_Cl[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите коэффициент Cd " << i+1 << "-го самолета: ";
        coef_Cd[i] = inputpar();
    }
    for (int i = 0; i < size; i++) {
        cout << "Введите коэффициент Cl " << i+1 << "-го самолета: ";
        coef_Cl[i] = inputpar();
    }
    // подъемная сила L
    double L1[size];
    for (int i = 0; i < size; i++) {
        L1[i] = calculate_L1(V, P, coef_Cl[i], square[i]);
    }
    cout << "\n";
    for (int i = 0; i < size; i++) {
        cout << "Подъемная сила " << i+1 << "го самолета : " << L1[i] << endl;;
    }
    // СОПРОТИВЛЕНИЕ L
    double L2[size];
    for (int i = 0; i < size; i++) {
        L2[i] = calculate_L2(V, P, coef_Cd[i], square[i]);
    }
    cout << "\n";
    for (int i = 0; i < size; i++) {
        cout << "Сопротивление " << i + 1 << "го самолета : " << L2[i] << endl;;
    }
    //ускорение ay
    double ay[size];
    for (int i = 0; i < size; i++) {
        ay[i] = (L1[i] - weight[i] * g) / weight[i];
    }
    // завершить программу, т.к L может быть меньше веса.
    cout << "\n";
    for (int i = 0; i < size; i++) {
        cout << "Ускорение " << i + 1 << "го самолета : " << ay[i] << endl;;
    }
    // набор высоты h
    double h;
    cout << "Введите высоту: ";
    h = inputpar();
    double t[size];
    for (int i = 0; i < size; i++) {
        t[i] = pow(2 * h / ay[i], 0.5);
    }
    // находим минимальный элемент массива 
    int min;
    min = calculate_min(t);
    cout << "\nПервым наберет высоту самолет под номером: " << min << " за " << t[min-1] << " секунд.";

}

