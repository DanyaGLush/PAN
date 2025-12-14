#include <iostream>
#include <vector>
#include <iomanip>  
#include <cmath>     

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


    cout << left << setw(10) << "Время (с) "
        << setw(15) << "Высота (м)" << endl;
    cout << string(20, '-') << endl;


    cout << left << fixed << setprecision(2);

    for (size_t i = 0; i < times.size(); ++i) {
        cout << setw(10) << times[i]
            << setw(15) << heights[i] << endl;
    }
    
    if (heights.empty()) {
        cout << "Данных нет! Вектор heights пуст." << std::endl;
        return 0; 
    }

    cout << "Способ 1" << endl;

    size_t idx_max = 0; 

    for (size_t i = 1; i < heights.size(); ++i) {
        if (heights[i] > heights[idx_max]) {
            idx_max = i; 
        }
    }
    
    cout << "Максимальная высота: " << heights[idx_max]
        << " м" << std::endl;
    cout << "Время достижения: " << times[idx_max]
        << " с" << std::endl;
    cout << "Индекс в векторе: " << idx_max << std::endl;

    cout << "Способ 2(встроенная функция)" << endl;

    auto it_max = max_element(heights.begin(), heights.end());
        
    size_t idx_max_stl = distance(heights.begin(), it_max);

    cout << "Максимальная высота: " << *it_max
        << " м" << endl;
    cout << "Время достижения: " << times[idx_max_stl]
        << " с" << endl;
    cout << "Индекс в векторе: " << idx_max_stl << endl;
}