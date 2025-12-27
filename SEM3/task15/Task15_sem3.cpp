#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<double> coordinates = { 15.3, 10.5, 25.3, 10.5, 45.7, 15.3, 60.2, 25.3 };

    sort(coordinates.begin(), coordinates.end());

    auto new_end = unique(coordinates.begin(), coordinates.end());
    coordinates.erase(new_end, coordinates.end());

    for (size_t i = 0; i < coordinates.size(); ++i) {
        cout << coordinates[i] << " ";
    }

    return 0;
}
