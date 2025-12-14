

#include <iostream>

using namespace std;

const double g = 9.81;

double input_par()
{
    double num;
    while (!(cin >> num) || num <= 0)
    {
        cout << "Ошибка!!! Введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return num;
}

bool calculating(double l_min, double l_max, double p, double m, double h)
{
    double ay, t;
    double min_t = numeric_limits<double>::max();;
    double ind = l_min;
    double eps = 1e-10;
    for (double i = l_min; i < l_max + p + 0.1; i = i + p)
    {
        if (i > l_max)
        {
            if (l_max <= m * g)
            {
                cout << "Самолет не будет набирать высоту, введите корректные значения: ";
                return false;
            }
            else
            {
                ay = (l_max - m * g) / m;
                t = sqrt(2 * h / ay);
                cout << "Подъемная сила: " << l_max << " ускорение: " << ay << " время: " << t << endl;
            }
            if (t < min_t) {
               min_t = t;
               ind = l_max;
            }
        }
        else
        {
            if (i <= m * g)
            {
                cout << "Самолет не будет набирать высоту, введите корректные значения: ";
                return false;
            }

            else
            {
                ay = (i - m * g) / m;
                t = sqrt(2 * h / ay);
                cout << "Подъемная сила: " << i << " ускорение: " << ay << " время: " << t << endl;
            }

            if (t < min_t) {
                min_t = t;
                ind = i;
            }

        }

    }
    cout << "Оптимальное значение подъемной силы: " << ind << " , время набора заданной высоты составит: " << min_t;
    return true;
}

int main()
{

    double l_min, l_max, p, m, h;
    cout << "Введите массу самолета: ";
    m = input_par();
    cout << "Введите высоту: ";
    h = input_par();
    cout << "Введите минимальное значение подъемной силы: ";
    l_min = input_par();
    cout << "Введите максисальное значение подъемной силы: ";
    l_max = input_par();
    cout << "Введите шаг: ";
    p = input_par();
    calculating(l_min, l_max, p, m, h);
   
}


