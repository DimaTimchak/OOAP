#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <limits>

class SalaryCalculator {
public:
    virtual double calculateSalary() const = 0;
    virtual ~SalaryCalculator() = default;
};

class HourlySalaryCalculator : public SalaryCalculator {
    double hourlyRate;
    int hoursWorked;

public:
    HourlySalaryCalculator(double rate, int hours)
        : hourlyRate(rate), hoursWorked(hours) {}

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
};

class PieceworkSalaryCalculator : public SalaryCalculator {
    double pieceRate;
    int piecesCompleted;

public:
    PieceworkSalaryCalculator(double rate, int pieces)
        : pieceRate(rate), piecesCompleted(pieces) {}

    double calculateSalary() const override {
        return pieceRate * piecesCompleted;
    }
};

class Employee {
protected:
    std::string name;
    std::string position;
    std::shared_ptr<SalaryCalculator> salaryCalculator;

public:
    Employee(const std::string& name, const std::string& position, std::shared_ptr<SalaryCalculator> calculator)
        : name(name), position(position), salaryCalculator(calculator) {}

    virtual void printSalary() const {
        std::cout << "Employee: " << name << "\n"
            << "Position: " << position << "\n"
            << "Salary: " << salaryCalculator->calculateSalary() << "\n";
    }

    virtual ~Employee() = default;
};

template <typename T>
T safeInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please try again.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            return value;
        }
    }
}

void showMenu() {
    std::cout << "\n--- MENU ---\n";
    std::cout << "1. Add Employee\n";
    std::cout << "2. Show All Employees\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void addEmployee(std::vector<std::shared_ptr<Employee>>& employees) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name, position;
    int calcType;

    std::cout << "Enter employee name: ";
    std::getline(std::cin, name);
    std::cout << "Enter employee position: ";
    std::getline(std::cin, position);

    calcType = safeInput<int>("Select salary calculation method:\n1. Hourly\n2. Piecework\nEnter your choice: ");

    std::shared_ptr<SalaryCalculator> calculator;

    if (calcType == 1) {
        double hourlyRate = safeInput<double>("Enter hourly rate: ");
        int hoursWorked = safeInput<int>("Enter hours worked: ");
        calculator = std::make_shared<HourlySalaryCalculator>(hourlyRate, hoursWorked);
    }
    else if (calcType == 2) {
        double pieceRate = safeInput<double>("Enter piece rate: ");
        int piecesCompleted = safeInput<int>("Enter number of pieces completed: ");
        calculator = std::make_shared<PieceworkSalaryCalculator>(pieceRate, piecesCompleted);
    }
    else {
        std::cout << "Invalid choice. Returning to menu.\n";
        return;
    }

    employees.push_back(std::make_shared<Employee>(name, position, calculator));
    std::cout << "Employee added successfully.\n";
}

void showAllEmployees(const std::vector<std::shared_ptr<Employee>>& employees) {
    if (employees.empty()) {
        std::cout << "No employees added yet.\n";
        return;
    }

    for (const auto& employee : employees) {
        employee->printSalary();
        std::cout << "-------------------\n";
    }
}

int main() {
    std::vector<std::shared_ptr<Employee>> employees;
    int choice;

    do {
        showMenu();
        choice = safeInput<int>("");

        switch (choice) {
        case 1:
            addEmployee(employees);
            break;
        case 2:
            showAllEmployees(employees);
            break;
        case 3:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
