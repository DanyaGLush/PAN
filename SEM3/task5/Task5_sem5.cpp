
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    
    const double vx = 30.0;  
    const double vy = 20.0;  
    const double vz = 40.0;  
    const double dt = 1.0;   
    const double t_max = 10.0; 

    struct Point {
        double x, y, z;
    };

    vector<Point> traj;
  
    double x = 0.0, y = 0.0, z = 0.0;

    for (double t = 0.0; t <= t_max; t += dt) {
      
        traj.push_back({ x, y, z });

        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
    }

    cout << left << setw(8) << "t (с)"
        << setw(12) << "x (м)"
        << setw(12) << "y (м)"
        << setw(12) << "z (м)" << endl;

    cout << string(44, '-') << endl;

    cout << fixed << setprecision(2);

    double current_time = 0.0;
    for (size_t i = 0; i < traj.size(); ++i) {
        cout << left << setw(8) << current_time
            << setw(12) << traj[i].x
            << setw(12) << traj[i].y
            << setw(12) << traj[i].z << endl;

        current_time += dt;
    }

    return 0;
}
