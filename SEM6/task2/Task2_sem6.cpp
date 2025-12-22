#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class TargetManager {
private:
    struct Target {
        int id;
        string name;
        double x, y, z;
        double priority;
        double distance;
    };

    vector<Target> targets;
    string filename = "targets.txt";

public:
    void addTarget(int id, const string& name, double x, double y, double z,
        double priority, double distance) {
        targets.push_back({ id, name, x, y, z, priority, distance });
    }

    bool removeTarget(int target_id) {
        for (auto it = targets.begin(); it != targets.end(); ++it) {
            if (it->id == target_id) {
                targets.erase(it);
                return true;
            }
        }
        return false;
    }

    void saveTargetToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            return;
        }

        for (const auto& target : targets) {
            file << target.id << "." << target.name << ","
                << target.x << "," << target.y << "," << target.z << ","
                << target.priority << "," << target.distance << "\n";
        }

        file.close();
    }

    void loadTargetsFromFile() {
        targets.clear();
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Target target;

            string id_name;
            getline(ss, id_name, ',');

            size_t dot_pos = id_name.find('.');
            if (dot_pos != string::npos) {
                target.id = stoi(id_name.substr(0, dot_pos));
                target.name = id_name.substr(dot_pos + 1);
            }

            string token;
            getline(ss, token, ',');
            target.x = stod(token);

            getline(ss, token, ',');
            target.y = stod(token);

            getline(ss, token, ',');
            target.z = stod(token);

            getline(ss, token, ',');
            target.priority = stod(token);

            getline(ss, token);
            target.distance = stod(token);

            targets.push_back(target);
        }

        file.close();
    }

    vector<Target> getHighPriorityTargets(double min_priority) {
        vector<Target> highPriority;
        for (const auto& target : targets) {
            if (target.priority >= min_priority) {
                highPriority.push_back(target);
            }
        }
        return highPriority;
    }

    void sortByDistance() {
        sort(targets.begin(), targets.end(),
            [](const Target& a, const Target& b) {
                return a.distance < b.distance;
            });
    }

    void printAllTargets() {
        cout << "Цели в системе:\n";
        for (const auto& target : targets) {
            cout << "ID: " << target.id
                << ", " << target.name
                << ", Position: (" << target.x
                << ", " << target.y
                << ", " << target.z
                << "), Priority: " << target.priority
                << ", Distance: " << target.distance << "\n";
        }
    }
};

int main() {
    
    {
        ofstream file("targets.txt");
        file << "1.Name1,100.5,200.3,50.0,0.8,1500.0\n";
        file << "2.Name2,150.2,180.7,300.0,0.9,2000.0\n";
        file << "3.Name3,50.0,50.0,10.0,0.1,500.0\n";
        file.close();
    }

    TargetManager manager;

    manager.loadTargetsFromFile();

    cout << "Загруженные цели:\n";
    manager.printAllTargets();

    manager.addTarget(4, "Name4", 200.0, 100.0, 20.0, 0.7, 1800.0);

    cout << "\nПосле добавления цели:\n";
    manager.printAllTargets();

    manager.sortByDistance();

    cout << "\nПосле сортировки по расстоянию:\n";
    manager.printAllTargets();

    manager.saveTargetToFile();

    return 0;
}
