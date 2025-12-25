#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class Trajectory {
private:
    vector<double> t; 
    vector<double> x; 

public:
   
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось открыть файл " << filename << endl;
            return false;
        }

        string line;
        bool firstLine = true; 

        while (getline(file, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }

            if (line.empty()) continue;

            istringstream iss(line);
            string token;
            vector<string> tokens;

            while (getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() != 2) {
                cerr << "Предупреждение: некорректная строка — пропущена: " << line << endl;
                continue;
            }

            try {
                double time_val = stod(tokens[0]);
                double x_val = stod(tokens[1]);

                t.push_back(time_val);
                x.push_back(x_val);
            }
            catch (const exception& e) {
                cerr << "Ошибка при парсинге строки: " << line << " — " << e.what() << endl;
                continue;
            }
        }

        file.close();
        cout << "Загружено " << t.size() << " точек траектории." << endl;
        return true;
    }

   
    vector<double> calculateVelocities() const {
        if (t.size() < 2) {
            cerr << "Ошибка: недостаточно точек для вычисления скорости." << endl;
            return {};
        }

        vector<double> velocities;
        velocities.reserve(t.size() - 1);

        
        auto computeVelocity = [](double x_next, double x_curr, double t_next, double t_curr) {
            if (t_next == t_curr) {
                throw runtime_error("Время не должно быть одинаковым для соседних точек.");
            }
            return (x_next - x_curr) / (t_next - t_curr);
            };

        for (size_t i = 0; i < t.size() - 1; ++i) {
            try {
                double v = computeVelocity(x[i + 1], x[i], t[i + 1], t[i]);
                velocities.push_back(v);
            }
            catch (const exception& e) {
                cerr << "Ошибка при вычислении скорости на шаге " << i << ": " << e.what() << endl;
                continue;
            }
        }

        cout << "Вычислено " << velocities.size() << " значений скорости." << endl;
        return velocities;
    }

    void generateGnuplotScript(const string& script_filename) const {
        ofstream script(script_filename);
        if (!script.is_open()) {
            cerr << "Ошибка: не удалось создать скрипт " << script_filename << endl;
            return;
        }

        script << "# Gnuplot скрипт для построения графика x(t)\n";
        script << "set terminal png size 800,600\n";
        script << "set output 'trajectory_x_t.png'\n";
        script << "set grid\n";
        script << "set xlabel 'Время t (с)'\n";
        script << "set ylabel 'Координата x (м)'\n";
        script << "set title 'Траектория x(t)'\n";
        script << "set key right top\n";
        script << "plot 'traj.csv' using 1:2 with linespoints title 'x(t)' pointtype 7 linewidth 2\n";

        script.close();
        cout << "Скрипт для Gnuplot сохранён: " << script_filename << endl;
    }

 
    void printData() const {
        cout << "\n=== Данные траектории ===" << endl;
        for (size_t i = 0; i < t.size(); ++i) {
            cout << "t=" << t[i] << ", x=" << x[i] << endl;
        }
    }

    const vector<double>& getT() const { return t; }
    const vector<double>& getX() const { return x; }
};


int main() {
    Trajectory traj;

    
    if (!traj.loadFromFile("traj.csv")) {
        cerr << "Не удалось загрузить данные." << endl;
        return 1;
    }

    traj.printData();

    vector<double> velocities = traj.calculateVelocities();

   
    cout << "\n=== Скорости ===" << endl;
    for (size_t i = 0; i < velocities.size(); ++i) {
        cout << "v_" << i << " = " << velocities[i] << " м/с" << endl;
    }

    traj.generateGnuplotScript("plot_xt.gp");

    cout << "\n Готово! " << endl;

    return 0;
}