#include <iostream>
#include <string>

class Phone {
public:
    virtual std::string getModel() const = 0;
    virtual double getPrice() const = 0;
    virtual int getDeliveryTime() const = 0;
    virtual ~Phone() = default;
};

class USAPhone : public Phone {
public:
    std::string getModel() const override {
        return "Phone Model USA";
    }
    double getPrice() const override {
        return 1000.0;
    }
    int getDeliveryTime() const override {
        return 7;
    }
};

class EastCountryPhone : public Phone {
public:
    std::string getModel() const override {
        return "Phone Model East";
    }
    double getPrice() const override {
        return 700.0; 
    }
    int getDeliveryTime() const override {
        return 14;
    }
};
    
class PhoneFactory {
public:
    virtual Phone* createPhone() const = 0;
    virtual ~PhoneFactory() = default;
};

class USAFactory : public PhoneFactory {
public:
    Phone* createPhone() const override {
        return new USAPhone();
    }
};

class EastCountryFactory : public PhoneFactory {
public:
    Phone* createPhone() const override {
        return new EastCountryPhone();
    }
};


class OnlineStore {
private:
    PhoneFactory* factory;
public:
    explicit OnlineStore(PhoneFactory* factory) : factory(factory) {}

    void orderPhone() const {
        Phone* phone = factory->createPhone();
        std::cout << "Model: " << phone->getModel() << std::endl;
        std::cout << "Price: $" << phone->getPrice() << std::endl;
        std::cout << "Delivery time: " << phone->getDeliveryTime() << " days" << std::endl;
        delete phone;
    }
};

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int choice;
    
    while (true) {
        std::cout << "Select manufacturer country: (1) USA, (2) East Country\n";
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

    PhoneFactory* factory = nullptr;
    if (choice == 1) {
        factory = new USAFactory();
    }
    else if (choice == 2) {
        factory = new EastCountryFactory();
    }
    else {
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }

    OnlineStore store(factory);
    store.orderPhone();

    delete factory;

    return 0;
}
