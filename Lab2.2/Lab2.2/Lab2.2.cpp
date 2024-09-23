#include <iostream>
#include <string>

class Car {
public:
    std::string engineType;
    double engineVolume;
    bool hasABS;
    bool hasESP;
    int airbags;
    bool hasOnboardComputer;
    std::string climateControl;
    std::string interior;
    double price;

    void showSpecifications() const {
        std::cout << "Engine Type: " << engineType << std::endl;
        std::cout << "Engine Volume: " << engineVolume << " L" << std::endl;
        std::cout << "ABS: " << (hasABS ? "Yes" : "No") << std::endl;
        std::cout << "ESP: " << (hasESP ? "Yes" : "No") << std::endl;
        std::cout << "Airbags: " << airbags << std::endl;
        std::cout << "Onboard Computer: " << (hasOnboardComputer ? "Yes" : "No") << std::endl;
        std::cout << "Climate Control: " << climateControl << std::endl;
        std::cout << "Interior: " << interior << std::endl;
        std::cout << "Price: $" << price << std::endl;
    }
};

class CarBuilder {
public:
    virtual ~CarBuilder() = default;
    virtual void setEngineType() = 0;
    virtual void setEngineVolume() = 0;
    virtual void setABS() = 0;
    virtual void setESP() = 0;
    virtual void setAirbags() = 0;
    virtual void setOnboardComputer() = 0;
    virtual void setClimateControl() = 0;
    virtual void setInterior() = 0;
    virtual void setPrice() = 0;
    virtual Car* getCar() = 0;
};

class BaseCarBuilder : public CarBuilder {
private:
    Car* car;
public:
    BaseCarBuilder() { car = new Car(); }
    ~BaseCarBuilder() { delete car; }

    void setEngineType() override {
        car->engineType = "Petrol";
    }

    void setEngineVolume() override {
        car->engineVolume = 1.4;
    }

    void setABS() override {
        car->hasABS = false;
    }

    void setESP() override {
        car->hasESP = false;
    }

    void setAirbags() override {
        car->airbags = 2;
    }

    void setOnboardComputer() override {
        car->hasOnboardComputer = false;
    }

    void setClimateControl() override {
        car->climateControl = "None";
    }

    void setInterior() override {
        car->interior = "Fabric";
    }

    void setPrice() override {
        car->price = 15000;
    }

    Car* getCar() override {
        return car;
    }
};

class ComfortCarBuilder : public CarBuilder {
private:
    Car* car;
public:
    ComfortCarBuilder() { car = new Car(); }
    ~ComfortCarBuilder() { delete car; }

    void setEngineType() override {
        car->engineType = "Petrol";
    }

    void setEngineVolume() override {
        car->engineVolume = 1.6;
    }

    void setABS() override {
        car->hasABS = true;
    }

    void setESP() override {
        car->hasESP = true;
    }

    void setAirbags() override {
        car->airbags = 4;
    }

    void setOnboardComputer() override {
        car->hasOnboardComputer = true;
    }

    void setClimateControl() override {
        car->climateControl = "Air Conditioner";
    }

    void setInterior() override {
        car->interior = "Improved Fabric";
    }

    void setPrice() override {
        car->price = 20000;
    }

    Car* getCar() override {
        return car;
    }
};

class LuxuryCarBuilder : public CarBuilder {
private:
    Car* car;
public:
    LuxuryCarBuilder() { car = new Car(); }
    ~LuxuryCarBuilder() { delete car; }

    void setEngineType() override {
        car->engineType = "Diesel";
    }

    void setEngineVolume() override {
        car->engineVolume = 2.0;
    }

    void setABS() override {
        car->hasABS = true;
    }

    void setESP() override {
        car->hasESP = true;
    }

    void setAirbags() override {
        car->airbags = 6;
    }

    void setOnboardComputer() override {
        car->hasOnboardComputer = true;
    }

    void setClimateControl() override {
        car->climateControl = "Climate Control";
    }

    void setInterior() override {
        car->interior = "Leather";
    }

    void setPrice() override {
        car->price = 30000;
    }

    Car* getCar() override {
        return car;
    }
};

class PremiumCarBuilder : public CarBuilder {
private:
    Car* car;
public:
    PremiumCarBuilder() { car = new Car(); }
    ~PremiumCarBuilder() { delete car; }

    void setEngineType() override {
        car->engineType = "Electric";
    }

    void setEngineVolume() override {
        car->engineVolume = 0.0; // Electric cars have no volume
    }

    void setABS() override {
        car->hasABS = true;
    }

    void setESP() override {
        car->hasESP = true;
    }

    void setAirbags() override {
        car->airbags = 8;
    }

    void setOnboardComputer() override {
        car->hasOnboardComputer = true;
    }

    void setClimateControl() override {
        car->climateControl = "Advanced Climate Control";
    }

    void setInterior() override {
        car->interior = "Premium Leather";
    }

    void setPrice() override {
        car->price = 45000;
    }

    Car* getCar() override {
        return car;
    }
};

class CarDirector {
private:
    CarBuilder* builder;
public:
    void setBuilder(CarBuilder* newBuilder) {
        builder = newBuilder;
    }

    void buildCar() {
        builder->setEngineType();
        builder->setEngineVolume();
        builder->setABS();
        builder->setESP();
        builder->setAirbags();
        builder->setOnboardComputer();
        builder->setClimateControl();
        builder->setInterior();
        builder->setPrice();
    }

    Car* getCar() {
        return builder->getCar();
    }
};

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    CarDirector director;
    CarBuilder* baseBuilder = new BaseCarBuilder();
    CarBuilder* comfortBuilder = new ComfortCarBuilder();
    CarBuilder* luxuryBuilder = new LuxuryCarBuilder();
    CarBuilder* premiumBuilder = new PremiumCarBuilder();

    int choice;
    while (true) {
        std::cout << "Select configuration: (1) Base, (2) Comfort, (3) Luxury, (4) Premium\n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input! Please enter a number.\n";
            clearInputStream();
            continue;
        }

        if (choice == 1 || choice == 2) {
            break;
        }

        std::cout << "Invalid choice! Please select 1 or 2.\n";
    }

    switch (choice) {
    case 1:
        director.setBuilder(baseBuilder);
        break;
    case 2:
        director.setBuilder(comfortBuilder);
        break;
    case 3:
        director.setBuilder(luxuryBuilder);
        break;
    case 4:
        director.setBuilder(premiumBuilder);
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }

    director.buildCar();
    Car* car = director.getCar();

    std::cout << "\nCar Specifications:\n";
    car->showSpecifications();

    delete baseBuilder;
    delete comfortBuilder;
    delete luxuryBuilder;
    delete premiumBuilder;

    return 0;
}
