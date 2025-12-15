#include <iostream>
#include <vector>
#include <iomanip>  
#include <cmath>     
#include <algorithm>  

using namespace std;

int main() {
    const double v0 = 50;
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

    cout << left << setw(10) << "Время (с) "
        << setw(15) << "Высота (м)" << endl;
    cout << string(20, '-') << endl;

    cout << left << fixed << setprecision(2);

    for (size_t i = 0; i < times.size(); ++i) {
        cout << setw(10) << times[i]
            << setw(15) << heights[i] << endl;
    }

    auto new_end = remove_if(heights.begin(), heights.end(), [](double h) {
            return h < 10.0;  
        });

    heights.erase(new_end, heights.end());

    cout << "\nПосле удаления значений < 10 м:" << endl;

    if (heights.empty()) {
        cout << "Вектор стал пустым (все значения были < 10 м)" << endl;
    }
    else {
        cout << "Содержимое: ";
        for (double h : heights) {
            cout << h << " ";
        }
        cout << endl;
    }

    return 0;
}