#include <iostream>
#include <map>

struct Employee {
    int id;
    std::string name;
    std::string surname;
    std::string position;
    int departmentId;  // Зовнішній ключ, що посилається на id у таблиці "Відділи"
};

struct Department {
    int id;
    std::string name;
};

std::map<int, Employee> employees;
std::map<int, Department> departments;

void assignEmployeeToDepartment(int employeeId, int departmentId) {
    employees[employeeId].departmentId = departmentId;
}

int main() {
    // Приклади додавання даних
    departments[1] = {1, "IT вiддiл"};
    employees[1] = {1, "Анна", "Колько", "Розробник", 1};

    // Додавання зв'язку
    assignEmployeeToDepartment(1, 1);

    // Виведення інформації
    std::cout << "Employee ID: " << employees[1].id << std::endl;
    std::cout << "Employee Name: " << employees[1].name << std::endl;
    std::cout << "Employee Surname: " << employees[1].surname << std::endl;
    std::cout << "Employee Position: " << employees[1].position << std::endl;
    std::cout << "Employee Department ID: " << employees[1].departmentId << std::endl;
    std::cout << "Employee Department Name: " << departments[employees[1].departmentId].name << std::endl;

    return 0;
}
