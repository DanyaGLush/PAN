#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

class Rocket {
private:
    double x, y;     
    double vx, vy;    
    double g;         

public:
    
    Rocket(double startX, double startY, double startVx, double startVy)
        : x(startX), y(startY), vx(startVx), vy(startVy), g(9.8) {
    }

   
    void updatePosition(double dt) {
        x += vx * dt;          
        y += vy * dt;           
        vy -= g * dt;          
    }

    void changeVelocity(double deltaVx, double deltaVy) {
        vx += deltaVx;
        vy += deltaVy;
    }

    Point getPosition() const {
        return { x, y };
    }

    pair<double, double> getVelocity() const {
        return { vx, vy };
    }
};

int main() {
    const double dt = 1.0;      
    const double T = 10.0;      

    vector<Rocket> squad;
    squad.reserve(5);

    squad.emplace_back(1000, 10, 0, 50);    
    squad.emplace_back(900, 15, -5, 40);    
    squad.emplace_back(1100, 5, 5, 45);     
    squad.emplace_back(950, 20, -3, 35);    
    squad.emplace_back(1050, 0, 3, 55);     

    vector<vector<Point>> trajectories(5);

    for (double t = 0; t <= T; t += dt) {
        for (size_t i = 0; i < squad.size(); ++i) {
            
            trajectories[i].push_back(squad[i].getPosition());

            squad[i].updatePosition(dt);
        }
    }

    cout << left << setw(10) << "Ракета"
        << setw(15) << " X (м)"
        << setw(15) << "Y (м)"
        << setw(20) << "Скорость (Vx, Vy)" << endl;
    cout << string(60, '-') << endl;

    cout << fixed << setprecision(2);

    for (size_t i = 0; i < squad.size(); ++i) {
        Point pos = squad[i].getPosition();
        auto velocity = squad[i].getVelocity();

        cout << left << setw(10) << i + 1
            << setw(15) << pos.x
            << setw(15) << pos.y
            << "(" << velocity.first << ", " << velocity.second << ") м/с" << endl;
    }

    return 0;
}
