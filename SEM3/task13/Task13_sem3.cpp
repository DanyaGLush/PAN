#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<double> temperatures = { 50.0, -150.0, 75.5, 250.0, 80.2, -50.0, 90.1, 300.0 };

    auto new_end = remove_if(temperatures.begin(), temperatures.end(),
        [](double temp) {
            return temp < -100.0 || temp > 200.0;
        });

    temperatures.erase(new_end, temperatures.end());

    for (size_t i = 0; i < temperatures.size(); ++i) {
        cout << temperatures[i] << " ";
    }
    cout << endl;

    return 0;
}