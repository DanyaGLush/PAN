#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class TelemetryLogger {
private:
    struct TelemetryData {
        double time;
        double altitude;
        double speed;
        double heading;
        double fuel;
    };

    string baseFilename = "telemetry";
    int fileCounter = 1;
    const int MAX_RECORDS_PER_FILE = 1000;
    int currentRecords = 0;

public:
    bool logData(double time, double altitude, double speed,
        double heading, double fuel) {

        rotateFileIfNeeded();

        string filename = baseFilename + "_" +
            to_string(fileCounter) + ".bin";

        ofstream file(filename, ios::binary | ios::app);
        if (!file.is_open()) {
            return false;
        }

        TelemetryData data = { time, altitude, speed, heading, fuel };
        file.write(reinterpret_cast<const char*>(&data), sizeof(TelemetryData));
        file.close();

        currentRecords++;
        return true;
    }

    void rotateFileIfNeeded() {
        if (currentRecords >= MAX_RECORDS_PER_FILE) {
            fileCounter++;
            currentRecords = 0;
        }
    }

    vector<TelemetryData> readLogFile(const string& filename) {
        vector<TelemetryData> data;
        ifstream file(filename, ios::binary);

        if (!file.is_open()) {
            return data;
        }

        TelemetryData record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(TelemetryData))) {
            data.push_back(record);
        }

        file.close();
        return data;
    }

    void printLogSummary() {
        string filename = baseFilename + "_" +
            to_string(fileCounter) + ".bin";

        auto data = readLogFile(filename);

        cout << "=== Сводка телеметрии ===\n";
        cout << "Файл: " << filename << "\n";
        cout << "Количество записей: " << data.size() << "\n";

        if (!data.empty()) {
            cout << "Временной диапазон: " << data.front().time
                << " - " << data.back().time << "\n";

            double minAltitude = data[0].altitude;
            double maxAltitude = data[0].altitude;
            double minSpeed = data[0].speed;
            double maxSpeed = data[0].speed;
            double minFuel = data[0].fuel;
            double maxFuel = data[0].fuel;

            for (const auto& record : data) {
                if (record.altitude < minAltitude) minAltitude = record.altitude;
                if (record.altitude > maxAltitude) maxAltitude = record.altitude;
                if (record.speed < minSpeed) minSpeed = record.speed;
                if (record.speed > maxSpeed) maxSpeed = record.speed;
                if (record.fuel < minFuel) minFuel = record.fuel;
                if (record.fuel > maxFuel) maxFuel = record.fuel;
            }

            cout << fixed << setprecision(1);
            cout << "Высота: " << minAltitude << " - " << maxAltitude << "\n";
            cout << "Скорость: " << minSpeed << " - " << maxSpeed << "\n";
            cout << "Топливо: " << minFuel << " - " << maxFuel << "\n";
        }
        cout << "=========================\n";
    }
};

int main() {
    TelemetryLogger logger;

    
    logger.logData(0.0, 100.0, 25.0, 45.0, 80.0);
    logger.logData(1.0, 105.0, 27.0, 46.0, 79.5);
    logger.logData(2.0, 110.0, 29.0, 47.0, 79.0);

    
    logger.printLogSummary();

    return 0;
}