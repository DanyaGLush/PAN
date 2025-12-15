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

    for (double t = 1; t <= 20; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;

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

    auto it = find_if(heights.begin(), heights.end(),
        [](double h) {
            return h <= 0.0;  
        });

    if (it == heights.end()) {
        cout << "Падения не было в диапазоне измерений." << endl;
        cout << "Все высоты положительные." << endl;
    }
    else {
        
        size_t idx = distance(heights.begin(), it);

        double t_fall = times[idx];
        double h_fall = heights[idx];

        cout << "Первый момент времени, когда высота <= 0:" << endl;
        cout << "Индекс: " << idx << endl;
        cout << "Время падения: " << t_fall << " с" << endl;
        cout << "Высота в этот момент: " << h_fall << " м" << endl;

        if (t_fall == 0.0) {
            cout << "Примечание: Высота на t=0 уже равна 0" << endl;
        }
    }

    return 0;
}
