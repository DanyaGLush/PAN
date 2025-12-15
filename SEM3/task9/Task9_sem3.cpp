#include <iostream>
#include <vector>
#include <iomanip>  
#include <cmath>     
#include <cstdlib>    
#include <ctime>      

using namespace std;

int main() {
    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 1.0;

    if (v0 <= 0) {
        cout << "Предупреждение: начальная скорость v0 должна быть положительной!" << endl;
        return 1;
    }

    vector<double> times;
    vector<double> heights;

    for (double t = 0.0; t <= 1000.0; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        if (h < 0.0) {
            break;
        }
        times.push_back(t);
        heights.push_back(h);
    }

    cout << "ИСХОДНАЯ ТРАЕКТОРИЯ" << endl;
    cout << left << setw(10) << "Время (с) "
        << setw(15) << "Высота (м)" << endl;
    cout << string(20, '-') << endl;
    cout << left << fixed << setprecision(2);

    for (size_t i = 0; i < times.size(); ++i) {
        cout << setw(10) << times[i]
            << setw(15) << heights[i] << endl;
    }

    srand(time(0));  

    vector<double> noisy_heights = heights;  

    for (size_t i = 0; i < noisy_heights.size(); ++i) {
        double noise = (rand() % 2000) / 100.0 - 10.0; 
        noisy_heights[i] += noise;
    }
    size_t n = noisy_heights.size();
    vector<double> smoothed(n);

    if (n >= 3) {
       
        smoothed[0] = noisy_heights[0];
        smoothed[n - 1] = noisy_heights[n - 1];

        for (size_t i = 1; i + 1 < n; ++i) {
            smoothed[i] = (noisy_heights[i - 1] + noisy_heights[i] + noisy_heights[i + 1]) / 3.0;
        }
    }
    else {
        smoothed = noisy_heights;
    }

    cout << "\nСРАВНЕНИЕ ВЫСОТ:" << endl;
    cout << "===============" << endl;

    cout << left << setw(8) << "Индекс"
        << setw(15) << "Шумные (м)"
        << setw(15) << "Сглаженные (м)"
        << setw(15) << "Исходные (м)" << endl;
    cout << string(53, '-') << endl;

    for (size_t i = 0; i < n; ++i) {
        cout << left << setw(8) << i
            << setw(15) << noisy_heights[i]
            << setw(15) << smoothed[i]
            << setw(15) << heights[i] << endl;
    }

    return 0;
}
