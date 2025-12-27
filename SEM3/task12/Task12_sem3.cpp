#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<double> sensor_data = { 0.1, 0.0, 2.3, 0.0, 4.5, 0.0, 0.0, 3.2 };

    int zero_count = count(sensor_data.begin(), sensor_data.end(), 0.0);

    cout << "Количество нулевых показаний: " << zero_count << endl;

    return 0;
}
