#include <iostream>
#include <vector>
#include <iomanip>

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
        cout << left << setw(10) << times[i]
            << setw(15) << velocities[i] << endl;
    }

    return 0;
}
