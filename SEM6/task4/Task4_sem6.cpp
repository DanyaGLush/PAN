#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

class WaypointManager {
private:
    struct Waypoint {
        int id;
        double x, y, z;
        double speed;
        string description;
    };

    vector<Waypoint> waypoints;
    string filename = "waypoints.txt";
    int currentIndex = 0;

public:
    void addWaypoint(int id, double x, double y, double z,
        double speed, const string& desc) {
        waypoints.push_back({ id, x, y, z, speed, desc });
    }

    bool saveRoute() {
        ofstream fout(filename, ios::out);
        if (!fout.is_open()) {
            return false;
        }

        for (const auto& wp : waypoints) {
            fout << wp.id << ","
                << wp.x << "," << wp.y << "," << wp.z << ","
                << wp.speed << "," << wp.description << "\n";
        }

        fout.close();
        return true;
    }

    bool loadRoute() {
        waypoints.clear();
        ifstream fin(filename, ios::in);
        if (!fin.is_open()) {
            return false;
        }

        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            Waypoint wp;
            char comma;

            ss >> wp.id >> comma;
            ss >> wp.x >> comma;
            ss >> wp.y >> comma;
            ss >> wp.z >> comma;
            ss >> wp.speed >> comma;
            getline(ss, wp.description);

            waypoints.push_back(wp);
        }

        fin.close();
        currentIndex = 0;
        return true;
    }

    double calculateTotalDistance() {
        double total = 0.0;
        for (size_t i = 1; i < waypoints.size(); ++i) {
            double dx = waypoints[i].x - waypoints[i - 1].x;
            double dy = waypoints[i].y - waypoints[i - 1].y;
            double dz = waypoints[i].z - waypoints[i - 1].z;
            total += sqrt(dx * dx + dy * dy + dz * dz);
        }
        return total;
    }

    Waypoint getNextWaypoint() {
        if (currentIndex < waypoints.size()) {
            return waypoints[currentIndex];
        }
        return { 0, 0.0, 0.0, 0.0, 0.0, "" };
    }

    bool checkWaypointReached(double x, double y, double z) {
        if (currentIndex >= waypoints.size()) {
            return false;
        }

        const auto& current = waypoints[currentIndex];
        double dx = x - current.x;
        double dy = y - current.y;
        double dz = z - current.z;
        double distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance < 10.0) {
            currentIndex++;
            return true;
        }

        return false;
    }

    void printRouteInfo() {
        cout << "Маршрут загружен: " << waypoints.size() << " точек\n";
        cout << "Общее расстояние: " << fixed << setprecision(1)
            << calculateTotalDistance() << " метров\n";

        if (!waypoints.empty() && currentIndex < waypoints.size()) {
            const auto& current = waypoints[currentIndex];
            cout << "Текущая точка: " << current.description
                << " (" << current.x << ", " << current.y << ", " << current.z << ")\n";

            if (currentIndex + 1 < waypoints.size()) {
                const auto& next = waypoints[currentIndex + 1];
                cout << "Следующая точка: " << next.description
                    << " (" << next.x << ", " << next.y << ", " << next.z << ")\n";
            }
        }
    }
};

int main() {
    {
        ofstream file("waypoints.txt");
        file << "1,0.0,0.0,100.0,25.0,Start\n";
        file << "2,100.0,50.0,150.0,30.0,CheckpointA\n";
        file << "3,200.0,100.0,200.0,35.0,CheckpointB\n";
        file.close();
    }

    WaypointManager manager;

    if (manager.loadRoute()) {
        cout << "Маршрут успешно загружен\n";
        manager.printRouteInfo();
    }

    return 0;
}