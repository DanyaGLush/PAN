#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric> 

using namespace std;

int main() {

    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 1.0;

    vector<double> times;
    vector<double> velocities;

    double t_max = 2 * v0 / g;

    for (double t = 0.0; t <= t_max; t += dt) {

        double v = v0 - g * t;

        times.push_back(t);
        velocities.push_back(v);

        if (v < -v0) {
            break;
        }
    }

    cout << left << setw(10) << "Время (с) "
        << setw(15) << "Скорость (м/с)" << endl;
    cout << string(24, '-') << endl;

    cout << left << fixed << setprecision(2);

    for (size_t i = 0; i < times.size(); ++i) {
        std::cout << std::left << std::setw(10) << times[i]
            << std::setw(15) << velocities[i] << std::endl;
    }

    if (velocities.empty()) {
        std::cout << "Ошибка: вектор скоростей пуст!" << std::endl;
        return 1;
    }

    double sum = accumulate(velocities.begin(), velocities.end(), 0.0);
    double avg = sum / velocities.size();

    cout << "Средняя скорость: " << avg << " м/с" << endl;

    return 0;
}