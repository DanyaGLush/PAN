#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<double> heights = { 0.0, 10.5, 25.3, 45.7, 60.2, 55.8, 40.1, 30.0 };

    auto max_it = max_element(heights.begin(), heights.end());

    cout << "Максимальная высота: " << *max_it << endl;
    cout << "Момент времени: " << distance(heights.begin(), max_it) << endl;

    return 0;
}
