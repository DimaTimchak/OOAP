#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

class SalesCounter {
private:
    int foodCount, medicineCount, clothingCount;
    double totalFoodCost, totalMedicineCost, totalClothingCost;

    SalesCounter() : foodCount(0), medicineCount(0), clothingCount(0),
        totalFoodCost(0.0), totalMedicineCost(0.0), totalClothingCost(0.0) {
        std::ofstream logFile("sales_log.txt", std::ios::out);
        if (logFile.is_open()) {
            logFile << "Sales log started\n";
            logFile.close();
        }
        std::srand(std::time(nullptr));
    }

    static SalesCounter* instance;

public:
    static SalesCounter* getInstance() {
        return instance;
    }

    void sellFood() {
        double basePrice = (std::rand() % 91) + 10; 
        double finalPrice = basePrice * 1.05;

        foodCount++;
        totalFoodCost += finalPrice;
        logSale("Food", finalPrice);
    }

    void sellMedicine() {
        double basePrice = (std::rand() % 91) + 10;
        double finalPrice = basePrice * 1.10; 

        medicineCount++;
        totalMedicineCost += finalPrice;
        logSale("Medicine", finalPrice);
    }

    void sellClothing() {
        double basePrice = (std::rand() % 91) + 10;
        double finalPrice = basePrice * 1.15; 

        clothingCount++;
        totalClothingCost += finalPrice;
        logSale("Clothing", finalPrice);
    }

    void logSale(const std::string& groupName, double price) {  
        std::ofstream logFile("sales_log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "Group: " << groupName << ", Price: " << price << "\n";
            logFile.close();
        }
    }

    void displayStats() const {
        std::cout << "Food sold: " << foodCount << ", Total cost: " << totalFoodCost << "\n";
        std::cout << "Medicine sold: " << medicineCount << ", Total cost: " << totalMedicineCost << "\n";
        std::cout << "Clothing sold: " << clothingCount << ", Total cost: " << totalClothingCost << "\n";
    }
};

SalesCounter* SalesCounter::instance = new SalesCounter();

bool isNumber(const std::string& str) {
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

int main() {
    SalesCounter* counter = SalesCounter::getInstance();
    std::string choice;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Sell Food\n";
        std::cout << "2. Sell Medicine\n";
        std::cout << "3. Sell Clothing\n";
        std::cout << "4. Show Sales Stats\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (!isNumber(choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        int option = std::stoi(choice);

        switch (option) {
        case 1:
            counter->sellFood();
            std::cout << "Food sold!\n";
            break;
        case 2:
            counter->sellMedicine();
            std::cout << "Medicine sold!\n";
            break;
        case 3:
            counter->sellClothing();
            std::cout << "Clothing sold!\n";
            break;
        case 4:
            counter->displayStats();
            break;
        case 0:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid option, please try again.\n";
        }
    }

    return 0;
}
