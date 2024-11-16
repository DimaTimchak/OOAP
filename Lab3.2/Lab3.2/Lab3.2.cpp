#include <iostream>
#include <string>
#include <limits>

class Customer {
public:
    virtual void displayDetails() const = 0;  
    virtual ~Customer() = default;
};

class FullPaymentCustomer : public Customer {
private:
    std::string name;
    std::string carModel;
    double price;
public:
    FullPaymentCustomer(const std::string& name, const std::string& carModel, double price)
        : name(name), carModel(carModel), price(price) {}

    void displayDetails() const override {
        std::cout << "Customer: " << name << "\n"
            << "Car Model: " << carModel << "\n"
            << "Price (Full Payment): " << price << "\n"
            << "Insurance: Comprehensive\n"
            << "Warranty: 5 years\n";
    }
};

class CreditCustomer : public Customer {
private:
    std::string name;
    std::string carModel;
    double price;
public:
    CreditCustomer(const std::string& name, const std::string& carModel, double price)
        : name(name), carModel(carModel), price(price) {}

    void displayDetails() const override {
        std::cout << "Customer: " << name << "\n"
            << "Car Model: " << carModel << "\n"
            << "Price (Credit): " << price << "\n"
            << "Insurance: Basic\n"
            << "Warranty: 3 years\n";
    }
};

class InstallmentCustomer : public Customer {
private:
    std::string name;
    std::string carModel;
    double price;
public:
    InstallmentCustomer(const std::string& name, const std::string& carModel, double price)
        : name(name), carModel(carModel), price(price) {}

    void displayDetails() const override {
        std::cout << "Customer: " << name << "\n"
            << "Car Model: " << carModel << "\n"
            << "Price (Installment): " << price << "\n"
            << "Insurance: Standard\n"
            << "Warranty: 4 years\n";
    }
};

class CustomerFactory {
public:
    virtual Customer* createCustomer(const std::string& name, const std::string& carModel, double price) = 0;
    virtual ~CustomerFactory() = default;
};


class FullPaymentCustomerFactory : public CustomerFactory {
public:
    Customer* createCustomer(const std::string& name, const std::string& carModel, double price) override {
        return new FullPaymentCustomer(name, carModel, price);
    }
};

class CreditCustomerFactory : public CustomerFactory {
public:
    Customer* createCustomer(const std::string& name, const std::string& carModel, double price) override {
        return new CreditCustomer(name, carModel, price);
    }
};

class InstallmentCustomerFactory : public CustomerFactory {
public:
    Customer* createCustomer(const std::string& name, const std::string& carModel, double price) override {
        return new InstallmentCustomer(name, carModel, price);
    }
};


bool isValidPrice(const std::string& str) {
    for (char const& c : str) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

// Функція для перевірки введення на ціле число
bool isValidInt(const std::string& str) {
    for (char const& c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

double getValidPrice() {
    std::string input;
    double price;
    while (true) {
        std::cout << "Enter car price: ";
        std::cin >> input;
        if (isValidPrice(input)) {
            price = std::stod(input);
            return price;
        }
        else {
            std::cout << "Invalid input! Please enter a valid price.\n";
        }
    }
}

int getValidClientType() {
    std::string input;
    int type;
    while (true) {
        std::cout << "\nSelect payment option:\n";
        std::cout << "1. Full Payment\n";
        std::cout << "2. Credit\n";
        std::cout << "3. Installment\n";
        std::cout << "Your choice: ";
        std::cin >> input;
        if (isValidInt(input)) {
            type = std::stoi(input);
            if (type >= 1 && type <= 3) {
                return type;
            }
            else {
                std::cout << "Invalid choice! Please enter 1, 2 or 3.\n";
            }
        }
        else {
            std::cout << "Invalid input! Please enter a valid number.\n";
        }
    }
}

std::string getValidName() {
    std::string name;
    while (true) {
        std::cout << "Enter customer name: ";
        std::getline(std::cin >> std::ws, name);
        if (!name.empty()) {
            return name;
        }
        else {
            std::cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }
}
std::string getValidCarModel() {
    std::string model;
    while (true) {
        std::cout << "Enter car model: ";
        std::getline(std::cin >> std::ws, model);
        if (!model.empty()) {
            return model;
        }
        else {
            std::cout << "Car model cannot be empty. Please enter a valid model.\n";
        }
    }
}

int main() {
    std::string name = getValidName();
    std::string carModel = getValidCarModel();
    double price = getValidPrice();
    int type = getValidClientType();

    CustomerFactory* factory = nullptr;
    Customer* customer = nullptr;

    switch (type) {
    case 1:
        factory = new FullPaymentCustomerFactory();
        break;
    case 2:
        factory = new CreditCustomerFactory();
        break;
    case 3:
        factory = new InstallmentCustomerFactory();
        break;
    default:
        std::cout << "Invalid choice.\n";
        return 0;
    }

    customer = factory->createCustomer(name, carModel, price);
    customer->displayDetails();

    delete customer;
    delete factory;

    return 0;
}
