#include <iostream>
#include <string>
#include <memory>

class VagonSystem {
public:
    virtual void chargeLaptop() const = 0;
    virtual ~VagonSystem() = default;
};

class NewVagonSystem : public VagonSystem {
public:
    void chargeLaptop() const override {
        MatchSocket();
    }

private:
    void MatchSocket() const {
        std::cout << "Charging laptop with modern socket in the new wagon.\n";
    }
};


class OldVagonSystem {
public:
    void ThinSocket() const {
        std::cout << "Providing power through old thin socket.\n";
    }
};

class AdapterOldToNew : public VagonSystem {
private:
    std::shared_ptr<OldVagonSystem> oldSystem;

public:
    AdapterOldToNew(std::shared_ptr<OldVagonSystem> oldSys) : oldSystem(std::move(oldSys)) {}

    void chargeLaptop() const override {
        std::cout << "Using adapter for the old wagon system.\n";
        oldSystem->ThinSocket();
    }
};

int main() {
    std::cout << "You are on a train heading to Kyiv for the competition.\n";

    std::shared_ptr<VagonSystem> newWagon = std::make_shared<NewVagonSystem>();
    std::cout << "In the new wagon:\n";
    newWagon->chargeLaptop();

    std::shared_ptr<OldVagonSystem> oldSystem = std::make_shared<OldVagonSystem>();
    std::shared_ptr<VagonSystem> adapter = std::make_shared<AdapterOldToNew>(oldSystem);

    std::cout << "\nIn the old wagon:\n";
    adapter->chargeLaptop();

    return 0;
}
