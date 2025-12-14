

#include <iostream>
#include <cmath>
#include <iomanip>

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

//Заполнение массивов
void input_mas(double *mas, int n) {
    for (int i = 0; i < n; i++) {
        mas[i] = inputpar();

    }
}
//Вывод массива
void output_mas(double* mas, int n) {
    for (int i = 0; i < n; i++) {
        cout << mas[i] << ' ';

    }
}

// Расчет подъемной силы и вывод таблицы

void power(double* speed, int n, double* air, double s, double cl) {
    double L;
    int m = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L = 0.5 * air[j] * pow(speed[i], 2) * s * cl;
            cout << setw(5) << m << "|"
                << setw(10) << speed[i] << "|"
                << setw(11) << air[j] << "|"
                << setw(16) << L << "|" << "\n" << "______________________________________________" << endl;
            m++;
        }
       
    }
}

int main()
{
    double s, cl;
    cout << "Введите площадь крыла самолета: ";
    s = inputpar();
    cout << "Введите коэффициент подъемной силы самолета: ";
    cl = inputpar();
    int n;
    cout << "Введите количество элементов массива скоростей и соответствующих значений плотности воздуха: ";
    cin >> n;
    double* speed = new double[n];
    double* air = new double[n];
    cout << "Введите значения скоростей: " << endl;
    input_mas(speed, n);
    cout << "Введите значения плотностей воздуха: "  << endl;
    input_mas(air, n);
    cout << "Введенные массивы: " << endl;
    output_mas(speed, n);
    cout << "\n";
    output_mas(air, n);

    //𝐿 = 12𝜌𝑉^2𝑆𝐶
    cout << "\nВычисленная подъемная чила" << endl;
    cout << " ШАГ | Скорость | Плотность | Подъемная сила |" << endl;
    cout << "______________________________________________" << endl;
    power(speed, n, air, s, cl);

    delete[] speed;
    delete[] air;
   
}


