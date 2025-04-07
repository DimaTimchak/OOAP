#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <vector>

// Interface
class IBuhgalteria {
public:
    virtual std::string getSalaryDate() = 0;
    virtual ~IBuhgalteria() = default;
};

// Accounting 
class RealBuhgalteria : public IBuhgalteria {
public:
    std::string getSalaryDate() override {
        std::cout << "[Accounting] Getting salary payment date...\n";

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dayDist(1, 30);
        int day = dayDist(gen);

        std::vector<std::string> months = {
                "January", "February", "March", "April", "May", "June",
                "July", "August", "September", "October", "November", "December"
        };

        std::uniform_int_distribution<> monthDist(0, months.size() - 1);
        std::string month = months[monthDist(gen)];

        return std::to_string(day) + " " + month + " 2025";
    }
};

// Proxy
class ZamistitBuhgaltera : public IBuhgalteria {
private:
    std::unique_ptr<RealBuhgalteria> realBuh;
    std::string cachedDate;

public:
    std::string getSalaryDate() override {
        if (cachedDate.empty()) {
            realBuh = std::make_unique<RealBuhgalteria>();
            cachedDate = realBuh->getSalaryDate();
        }
        else {
            std::cout << "[Proxy] Returning cached date...\n";
        }
        return cachedDate;
    }
};

// Employee
class Spivrobitnyk {
private:
    std::string name;
    IBuhgalteria& dostup;

public:
    Spivrobitnyk(const std::string& name, IBuhgalteria& dostup)
        : name(name), dostup(dostup) {}

    void zapytatyProZarplatu() {
        std::cout << name << " finds out: salary will be " << dostup.getSalaryDate() << "\n";
    }
};

int main() {
    ZamistitBuhgaltera proxy;

    Spivrobitnyk petro("Petro", proxy);
    Spivrobitnyk ivan("Ivan", proxy);
    Spivrobitnyk natalia("Natalia", proxy);

    petro.zapytatyProZarplatu();  // first appeal
    std::cout << "-----------------------------\n";
    ivan.zapytatyProZarplatu();   // proxy
    natalia.zapytatyProZarplatu();  // proxy


    return 0;
}
