#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

int main() {
    vector<double> coordinates = { 0.0, 10.5, 25.3, 45.7, 60.2, 55.8, 40.1, 30.0 };

    vector<double> differences(coordinates.size());
    adjacent_difference(coordinates.begin(), coordinates.end(), differences.begin());

    double total_path = accumulate(differences.begin() + 1, differences.end(), 0.0,
        [](double sum, double diff) {
            return sum + abs(diff);
        });

    cout << "Суммарный путь: " << total_path << endl;

    return 0;
}
