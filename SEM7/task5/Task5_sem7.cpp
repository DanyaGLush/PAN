#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

class MotionAnalyzer {
public:
    vector<double> t;  
    vector<double> x;  
    vector<double> v;  
    vector<double> a;  

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл: " + filename);
        }

        string line;
        getline(file, line); 

        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() != 2) continue;

            try {
                double time = stod(tokens[0]);
                double pos = stod(tokens[1]);

                t.push_back(time);
                x.push_back(pos);
            }
            catch (...) {
                cerr << "Ошибка парсинга строки: " << line << endl;
            }
        }

        file.close();
        cout << "Загружено " << t.size() << " точек.\n";
    }

    void computeVelocity() {
        if (t.size() < 2) {
            v.resize(t.size(), 0.0); 
            return;
        }

        v.resize(t.size());

        v[0] = 0.0;

        auto calc_velocity = [this](int i) -> double {
            double dt = t[i] - t[i - 1];
            if (dt == 0) return 0.0;
            return (x[i] - x[i - 1]) / dt;
            };

        for (size_t i = 1; i < t.size(); ++i) {
            v[i] = calc_velocity(i);
        }
    }

    void computeAcceleration() {
        if (v.size() < 2) {
            a.resize(v.size(), 0.0);
            return;
        }

        a.resize(v.size());

        a[0] = 0.0;

        for (size_t i = 1; i < v.size(); ++i) {
            auto calc_acceleration = [this, i]() -> double {
                double dt = t[i] - t[i - 1];
                if (dt == 0) return 0.0;
                return (v[i] - v[i - 1]) / dt;
                };
            a[i] = calc_acceleration();
        }
    }

    void saveResults(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Не удалось создать файл: " + filename);
        }

        file << "t,x,v,a\n";
        for (size_t i = 0; i < t.size(); ++i) {
            file << t[i] << "," << x[i] << "," << v[i] << "," << a[i] << "\n";
        }

        file.close();
        cout << "Результаты сохранены в файл: " << filename << endl;
    }

    void plotGraphs(const string& dataFile = "motion_processed.csv") {

        saveResults(dataFile);

        string gnuplotCmd = R"(
set terminal png size 1000,600
set output 'motion_analysis.png'
set xlabel 'Время t'
set grid
set title 'Анализ движения: скорость и ускорение'

plot ')" + dataFile + R"(' using 1:3 with linespoints lw 2 title 'v(t)', \
     ')" + dataFile + R"(' using 1:4 with linespoints lw 2 title 'a(t)'
)";

        FILE* gp = _popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist", "w"); 
        if (!gp) {
            cerr << "Ошибка: не удалось запустить GNUPlot через popen.\n";
            return;
        }

        fprintf(gp, "%s", gnuplotCmd.c_str());
        _pclose(gp); 

        cout << "Графики сохранены как motion_analysis.png\n";
    }
};

int main() {
    try {
        MotionAnalyzer analyzer;
        analyzer.loadFromFile("motion.csv");

        analyzer.computeVelocity();
        analyzer.computeAcceleration();

        analyzer.saveResults("motion_processed.csv");
        analyzer.plotGraphs();

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}