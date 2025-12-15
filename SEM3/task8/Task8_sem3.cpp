#include <iostream>
#include <vector>
#include <iomanip>  
#include <cmath>     
#include <algorithm>  

using namespace std;

int main() {
    
    const double v0_1 = 50.0;
    const double g = 9.8;
    const double dt = 1.0;

    if (v0_1 <= 0) {
        cout << "Предупреждение: начальная скорость v0 должна быть положительной!" << endl;
        return 1;
    }

    vector<double> times1;
    vector<double> heights1;

    for (double t = 0.0; t <= 1000.0; t += dt) {
        double h = v0_1 * t - 0.5 * g * t * t;
        if (h < 0.0) {
            break;
        }
        times1.push_back(t);
        heights1.push_back(h);
    }

    const double v0_2 = 40.0;  

    vector<double> times2;
    vector<double> heights2;

    for (double t = 0.0; t <= 1000.0; t += dt) {
        double h = v0_2 * t - 0.5 * g * t * t;
        if (h < 0.0) {
            break;
        }
        times2.push_back(t);
        heights2.push_back(h);
    }

    cout << "РАКЕТА 1 (v0 = " << v0_1 << " м/с)" << endl;
    cout << left << setw(10) << "Время (с) "
        << setw(15) << "Высота (м)" << endl;
    cout << string(20, '-') << endl;
    cout << left << fixed << setprecision(2);
    for (size_t i = 0; i < times1.size(); ++i) {
        cout << setw(10) << times1[i]
            << setw(15) << heights1[i] << endl;
    }

    cout << "\n\nРАКЕТА 2 (v0 = " << v0_2 << " м/с)" << endl;
    cout << left << setw(10) << "Время (с) "
        << setw(15) << "Высота (м)" << endl;
    cout << string(20, '-') << endl;
    for (size_t i = 0; i < times2.size(); ++i) {
        cout << setw(10) << times2[i]
            << setw(15) << heights2[i] << endl;
    }

    double max1 = 0.0, t_max1 = 0.0, t_fall1 = 0.0;

    if (!heights1.empty()) {
        
        auto max_it1 = max_element(heights1.begin(), heights1.end());
        max1 = *max_it1;
        size_t idx_max1 = distance(heights1.begin(), max_it1);
        t_max1 = times1[idx_max1];

        t_fall1 = times1.back() + dt;
    }

    double max2 = 0.0, t_max2 = 0.0, t_fall2 = 0.0;

    if (!heights2.empty()) {
        
        auto max_it2 = max_element(heights2.begin(), heights2.end());
        max2 = *max_it2;
        size_t idx_max2 = distance(heights2.begin(), max_it2);
        t_max2 = times2[idx_max2];

        t_fall2 = times2.back() + dt;
    }

   
    cout << "\nРАКЕТА 1:" << endl;
    cout << "  Максимальная высота: " << max1 << " м" << endl;
    cout << "  Время достижения максимума: " << t_max1 << " с" << endl;
    cout << "  Время падения: " << t_fall1 << " с" << endl;

    cout << "\nРАКЕТА 2:" << endl;
    cout << "  Максимальная высота: " << max2 << " м" << endl;
    cout << "  Время достижения максимума: " << t_max2 << " с" << endl;
    cout << "  Время падения: " << t_fall2 << " с" << endl;


    cout << "\n1. МАКСИМАЛЬНАЯ ВЫСОТА:" << endl;
    if (max1 > max2) {
        cout << "   Ракета 1 выше на " << (max1 - max2) << " м" << endl;
    }
    else if (max2 > max1) {
        cout << "   Ракета 2 выше на " << (max2 - max1) << " м" << endl;
    }
    else {
        cout << "   Ракеты поднялись на одинаковую высоту" << endl;
    }

    cout << "\n2. ВРЕМЯ ПОЛЕТА:" << endl;
    if (t_fall1 > t_fall2) {
        cout << "   Ракета 1 дольше в воздухе на " << (t_fall1 - t_fall2) << " с" << endl;
    }
    else if (t_fall2 > t_fall1) {
        cout << "   Ракета 2 дольше в воздухе на " << (t_fall2 - t_fall1) << " с" << endl;
    }
    else {
        cout << "   Ракеты находились в воздухе одинаковое время" << endl;
    }

    cout << left << setw(20) << "Параметр"
        << setw(15) << "Ракета 1"
        << setw(15) << "Ракета 2" << endl;
    cout << string(40, '-') << endl;

    cout << left << setw(20) << "Макс. высота (м)"
        << setw(15) << max1
        << setw(15) << max2 << endl;

    cout << left << setw(20) << "Время макс. (с)"
        << setw(15) << t_max1
        << setw(15) << t_max2 << endl;

    cout << left << setw(20) << "Время падения (с)"
        << setw(15) << t_fall1
        << setw(15) << t_fall2 << endl;

    return 0;
}