#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class DataValidator {
private:
    struct ValidationRule {
        string field;
        double min;
        double max;
    };

    vector<ValidationRule> rules;
    string filename = "validation_report.txt";

    struct ValidationResult {
        string field;
        double value;
        bool isValid;
        string message;
    };

    vector<ValidationResult> results;
    int totalChecks = 0;
    int passedChecks = 0;

public:
    void addValidationRule(const string& field, double min, double max) {
        rules.push_back({ field, min, max });
    }

    bool validateCoordinates(double x, double y, double z) {
        totalChecks += 3; 

        bool xValid = true, yValid = true, zValid = true;
        string message;

      
        for (const auto& rule : rules) {
            if (rule.field == "x") {
                if (x < rule.min || x > rule.max) {
                    xValid = false;
                    message = "координата X " + to_string(x) +
                        " выходит за пределы [" + to_string(rule.min) +
                        ", " + to_string(rule.max) + "]";
                }
            }
            else if (rule.field == "y") {
                if (y < rule.min || y > rule.max) {
                    yValid = false;
                    message = "координата Y " + to_string(y) +
                        " выходит за пределы [" + to_string(rule.min) +
                        ", " + to_string(rule.max) + "]";
                }
            }
            else if (rule.field == "z") {
                if (z < rule.min || z > rule.max) {
                    zValid = false;
                    message = "высота " + to_string(z) +
                        " превышает максимум " + to_string(rule.max);
                }
            }
        }

        bool overallValid = xValid && yValid && zValid;
        if (overallValid) {
            passedChecks += 3;
            results.push_back({ "Координаты", 0.0, true, "OK - все координаты в допустимых пределах" });
        }
        else {
            results.push_back({ "Координаты", 0.0, false,
                              "ОШИБКА - " + message });
        }

        return overallValid;
    }

    bool validateSpeed(double speed) {
        totalChecks++;

        for (const auto& rule : rules) {
            if (rule.field == "speed") {
                if (speed >= rule.min && speed <= rule.max) {
                    passedChecks++;
                    results.push_back({ "Скорость", speed, true,
                                      "OK - скорость в допустимых пределах" });
                    return true;
                }
                else {
                    results.push_back({ "Скорость", speed, false,
                                      "ОШИБКА - скорость " + to_string(speed) +
                                      " превышает максимум " + to_string(rule.max) });
                    return false;
                }
            }
        }

        results.push_back({ "Скорость", speed, false, "ОШИБКА - нет правила валидации для скорости" });
        return false;
    }

    bool validateAcceleration(double acceleration) {
        totalChecks++;

        for (const auto& rule : rules) {
            if (rule.field == "acceleration") {
                if (acceleration >= rule.min && acceleration <= rule.max) {
                    passedChecks++;
                    results.push_back({ "Ускорение", acceleration, true,
                                      "OK - ускорение в допустимых пределах" });
                    return true;
                }
                else {
                    results.push_back({ "Ускорение", acceleration, false,
                                      "ОШИБКА - ускорение " + to_string(acceleration) +
                                      " превышает максимум " + to_string(rule.max) });
                    return false;
                }
            }
        }

        results.push_back({ "Ускорение", acceleration, false, "ОШИБКА - нет правила валидации для ускорения" });
        return false;
    }

    void generateValidationReport() {
        ofstream fout(filename, ios::out);
        if (!fout.is_open()) {
            cerr << "Ошибка открытия файла для записи отчета\n";
            return;
        }

        fout << "Отчет валидации:\n";

        for (const auto& result : results) {
            fout << result.field << ": " << result.message << "\n";
        }

        double score = getValidationScore();
        fout << "Общий результат: " << fixed << setprecision(0)
            << score << "% данных валидны\n";

        fout.close();

        cout << "Отчет сохранен в файл: " << filename << "\n";
    }

    double getValidationScore() {
        if (totalChecks == 0) return 0.0;
        return (passedChecks * 100.0) / totalChecks;
    }
};

int main() {
    DataValidator validator;

    validator.addValidationRule("x", 0.0, 10000.0);
    validator.addValidationRule("y", 0.0, 10000.0);
    validator.addValidationRule("z", 0.0, 5000.0);  
    validator.addValidationRule("speed", 0.0, 300.0);  
    validator.addValidationRule("acceleration", -50.0, 20.0);  

    cout << "Проверка координат (5000.5, 3000.2, 10000.0): ";
    if (validator.validateCoordinates(5000.5, 3000.2, 10000.0)) {
        cout << "ВАЛИДНО\n";
    }
    else {
        cout << "НЕВАЛИДНО\n";
    }

    cout << "Проверка скорости (350.0): ";
    if (validator.validateSpeed(350.0)) {
        cout << "ВАЛИДНО\n";
    }
    else {
        cout << "НЕВАЛИДНО\n";
    }

    cout << "Проверка ускорения (25.0): ";
    if (validator.validateAcceleration(25.0)) {
        cout << "ВАЛИДНО\n";
    }
    else {
        cout << "НЕВАЛИДНО\n";
    }

    validator.generateValidationReport();

    cout << "\nОбщий результат валидации: "
        << validator.getValidationScore() << "%\n";

    return 0;
}
