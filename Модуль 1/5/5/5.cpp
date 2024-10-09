#include <iostream>
#include <vector>
#include <memory>
#include <limits> 

class User {
public:
    std::string name;

    User(const std::string& name)
        : name(name) {}
};

class Car {
private:
    std::string licensePlate;
    std::shared_ptr<User> currentUser;
    std::vector<std::shared_ptr<User>> previousUsers;

public:
    Car(const std::string& licensePlate)
        : licensePlate(licensePlate) {}

    std::shared_ptr<Car> changeOwner(std::shared_ptr<User> newUser) const {
        std::shared_ptr<Car> updatedCar = std::make_shared<Car>(*this);

        if (updatedCar->currentUser) {
            updatedCar->previousUsers.push_back(updatedCar->currentUser);
        }

        updatedCar->currentUser = newUser;

        return updatedCar;
    }

    void printOwners() const {
        if (currentUser) {
            std::cout << "Current owner: " << currentUser->name << std::endl;
        }
        else {
            std::cout << "No current owner." << std::endl;
        }

        if (!previousUsers.empty()) {
            std::cout << "Previous owners: " << std::endl;
            for (const auto& user : previousUsers) {
                std::cout << " - " << user->name << std::endl;
            }
        }
        else {
            std::cout << "No previous owners." << std::endl;
        }
    }

    std::string getLicensePlate() const {
        return licensePlate;
    }
};

bool isValidLicensePlate(const std::string& licensePlate) {
    if (licensePlate.size() != 8) {
        return false; 
    }
    for (size_t i = 0; i < licensePlate.size(); ++i) {
        if ((i < 2 || i >= 6) && !std::isalpha(licensePlate[i])) {
            return false;
        }
        if (i >= 2 && i < 6 && !std::isdigit(licensePlate[i])) {
            return false;
        }
    }
    return true;
}

void menu(std::vector<std::shared_ptr<Car>>& cars) {
    while (true) {
        std::cout << "\n===== Car Registration System =====" << std::endl;
        std::cout << "1. Register a new car" << std::endl;
        std::cout << "2. Change car owner" << std::endl;
        std::cout << "3. View car details" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int option;
        std::cout << "Select an option (1-4): ";
        std::cin >> option;

        if (std::cin.fail() || option < 1 || option > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            continue;
        }

        if (option == 1) {
            std::string licensePlate;
            std::cout << "Enter license plate (XX1234XX): ";
            std::cin >> licensePlate;
            if (!isValidLicensePlate(licensePlate)) {
                std::cout << "Invalid license plate format." << std::endl;
                continue;
            }
            auto newCar = std::make_shared<Car>(licensePlate);
            cars.push_back(newCar);
            std::cout << "Car registered successfully!" << std::endl;
        }
        else if (option == 2) {
            if (cars.empty()) {
                std::cout << "No cars available." << std::endl;
                continue;
            }

            std::cout << "Select a car by license plate to change owner: " << std::endl;
            for (size_t i = 0; i < cars.size(); ++i) {
                std::cout << i + 1 << ". " << cars[i]->getLicensePlate() << std::endl;
            }
            int carIndex;
            std::cin >> carIndex;
            if (carIndex < 1 || carIndex > cars.size()) {
                std::cout << "Invalid selection." << std::endl;
                continue;
            }
            std::string name;
            std::cout << "Enter new owner's name: ";
            std::cin.ignore(); 
            std::cin >> name;

            auto newUser = std::make_shared<User>(name);
            cars[carIndex - 1] = cars[carIndex - 1]->changeOwner(newUser);

            std::cout << "Owner changed successfully!" << std::endl;
        }
        else if (option == 3) {
            if (cars.empty()) {
                std::cout << "No cars available." << std::endl;
                continue;
            }

            std::cout << "Select a car by license plate to view details: " << std::endl;
            for (size_t i = 0; i < cars.size(); ++i) {
                std::cout << i + 1 << ". " << cars[i]->getLicensePlate() << std::endl;
            }

            int carIndex;
            std::cin >> carIndex;
            if (carIndex < 1 || carIndex > cars.size()) {
                std::cout << "Invalid selection." << std::endl;
                continue;
            }

            cars[carIndex - 1]->printOwners();
        }
        else if (option == 4) {
            break;
        }
    }
}

int main() {
    std::vector<std::shared_ptr<Car>> cars;
    menu(cars);  
    return 0;
}
