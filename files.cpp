#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

// Структура для представлення запису
struct Record {
    int id;
    int project_id;  // Нове поле для зв'язку
    std::string data;

    Record(int _id, int _project_id, const std::string& _data) : id(_id), project_id(_project_id), data(_data) {}
};

// Функція для збереження запису у файл
void saveRecordToFile(const std::string& filename, const Record& record) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << record.id << "," << record.project_id << "," << record.data << "\n";
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

// Функція для отримання запису з файлу за ідентифікатором
Record getRecordFromFile(const std::string& filename, int recordId) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ',');
            int id = std::stoi(token);
            if (id == recordId) {
                std::getline(iss, token, ',');
                int project_id = std::stoi(token);
                std::getline(iss, token);
                return Record(id, project_id, token);
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    return Record(-1, -1, "");  // Return an invalid record if not found
}

// Функція для видалення запису та всіх його підзаписів
void deleteRecordAndSubrecords(const std::string& filename, int recordId) {
    std::vector<Record> records;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ',');
            int id = std::stoi(token);
            if (id != recordId) {
                std::getline(iss, token, ',');
                int project_id = std::stoi(token);
                std::getline(iss, token);
                records.push_back(Record(id, project_id, token));
            }
        }
        file.close();

        // Оновлення файлу без видаленого запису
        std::ofstream outFile(filename, std::ios::trunc);
        for (const auto& record : records) {
            outFile << record.id << "," << record.project_id << "," << record.data << "\n";
        }
        outFile.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

// Функція для оновлення значення поля запису
void updateRecordField(const std::string& filename, int recordId, const std::string& newData) {
    std::vector<Record> records;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ',');
            int id = std::stoi(token);
            std::getline(iss, token, ',');
            int project_id = std::stoi(token);
            if (id == recordId) {
                records.push_back(Record(id, project_id, newData));
            } else {
                std::getline(iss, token);
                records.push_back(Record(id, project_id, token));
            }
        }
        file.close();

        // Оновлення файлу з новим значенням поля
        std::ofstream outFile(filename, std::ios::trunc);
        for (const auto& record : records) {
            outFile << record.id << "," << record.project_id << "," << record.data << "\n";
        }
        outFile.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

// Функція для виведення кількості записів у файлі
int countRecords(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
        file.close();
        return count;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
        return -1;
    }
}

// Функція для виведення всіх полів файлу
void printAllFields(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    // Тестові дані та виклик функцій
    Record masterRecord(1, "MasterData1");
    Record slaveRecord1(1, "SlaveData1");
    Record slaveRecord2(2, "SlaveData2");

    saveRecordToFile("master-file.txt", masterRecord);
    saveRecordToFile("slave-file.txt", slaveRecord1);
    saveRecordToFile("slave-file.txt", slaveRecord2);

    // Приклад виклику функцій
    Record retrievedMasterRecord = getRecordFromFile("master-file.txt", 1);
    std::cout << "Retrieved Master Record: " << retrievedMasterRecord.data << std::endl;

    deleteRecordAndSubrecords("slave-file.txt", 1);
    std::cout << "Deleted Slave Record 1 and its subrecords." << std::endl;

    updateRecordField("master-file.txt", 1, "UpdatedMasterData");
    std::cout << "Updated Master Record field." << std::endl;

    int totalMasterRecords = countRecords("master-file.txt");
    std::cout << "Total Master Records: " << totalMasterRecords << std::endl;

    printAllFields("slave-file.txt");

    return 0;
}
