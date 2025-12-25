#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath> 

using namespace std;

class SensorData {
private:
    vector<double> t;   
    vector<double> h1;  
    vector<double> h2;  
    vector<double> dh;  

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

            if (tokens.size() != 3) {
                cerr << "Предупреждение: некорректная строка — пропущена: " << line << endl;
                continue;
            }

            try {
                double time_val = stod(tokens[0]);
                double h1_val = stod(tokens[1]);
                double h2_val = stod(tokens[2]);

                t.push_back(time_val);
                h1.push_back(h1_val);
                h2.push_back(h2_val);
            }
            catch (const exception& e) {
                cerr << "Ошибка при парсинге строки: " << line << " — " << e.what() << endl;
                continue;
            }
        }

        file.close();
        cout << "Загружено " << t.size() << " точек данных." << endl;
        return true;
    }

    void calculateDifference() {
        if (h1.size() != h2.size()) {
            cerr << "Ошибка: размеры массивов h1 и h2 не совпадают." << endl;
            return;
        }

        dh.clear();
        dh.reserve(h1.size());

        auto computeDeltaH = [](double a, double b) {
            return abs(a - b);
            };

        for (size_t i = 0; i < h1.size(); ++i) {
            double delta = computeDeltaH(h1[i], h2[i]);
            dh.push_back(delta);
        }

        cout << "Вычислено " << dh.size() << " значений разницы Δh." << endl;
    }

    bool saveDifferenceToFile(const string& filename) {
        if (t.size() != dh.size()) {
            cerr << "Ошибка: данные не готовы для сохранения." << endl;
            return false;
        }

        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось создать файл " << filename << endl;
            return false;
        }

        file << "t,h1,h2,delta_h\n";

        for (size_t i = 0; i < t.size(); ++i) {
            file << t[i] << ","
                << h1[i] << ","
                << h2[i] << ","
                << dh[i] << "\n";
        }

        file.close();
        cout << "Разница успешно сохранена в файл: " << filename << endl;
        return true;
    }

    void generateGnuplotScript(const string& script_filename) const {
        fstream script(script_filename);
        if (!script.is_open()) {
            cerr << "Ошибка: не удалось создать скрипт " << script_filename << endl;
            return;
        }

        script << "# Gnuplot скрипт для построения трёх графиков на одном поле\n";
        script << "set terminal png size 1000,600\n";
        script << "set output 'sensor_comparison.png'\n";
        script << "set grid\n";
        script << "set xlabel 'Время t (с)'\n";
        script << "set ylabel 'Значение'\n";
        script << "set title 'Сравнение двух датчиков'\n";
        script << "set key outside right top\n";
        script << "plot 'sensors.csv' using 1:2 with linespoints title 'h1(t)' pointtype 7 linewidth 2, \\\n";
        script << "     'sensors.csv' using 1:3 with linespoints title 'h2(t)' pointtype 5 linewidth 2, \\\n";
        script << "     'diff.csv' using 1:4 with linespoints title 'Δh(t)' pointtype 9 linewidth 2\n";

        script.close();
        cout << "Скрипт для Gnuplot сохранён: " << script_filename << endl;
    }

    void printData() const {
        cout << "\n=== Данные датчиков ===" << endl;
        for (size_t i = 0; i < t.size(); ++i) {
            cout << "t=" << t[i]
                << ", h1=" << h1[i]
                << ", h2=" << h2[i]
                << ", Δh=" << dh[i] << endl;
        }
    }
};

int main() {
    SensorData sensor;

    if (!sensor.loadFromFile("sensors.csv")) {
        cerr << "Не удалось загрузить данные." << endl;
        return 1;
    }

    sensor.calculateDifference();

    if (!sensor.saveDifferenceToFile("diff.csv")) {
        cerr << "Не удалось сохранить разницу." << endl;
        return 1;
    }

    sensor.printData();

    sensor.generateGnuplotScript("plot_sensors.gp");

    return 0;
}