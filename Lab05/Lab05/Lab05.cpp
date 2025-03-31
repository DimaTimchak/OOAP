#include <iostream>
#include <vector>
#include <memory>
#include <limits>

// --- Weapon ---
class Weapon {
public:
    virtual int getDamage() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Weapon() = default;
};

class BasicWeapon : public Weapon {
public:
    int getDamage() const override { return 0; }
    std::string getName() const override { return "No weapon"; }
};

class Sword : public Weapon {
public:
    int getDamage() const override { return 15; }
    std::string getName() const override { return "Sword (Damage: 15)"; }
};

class Axe : public Weapon {
public:
    int getDamage() const override { return 20; }
    std::string getName() const override { return "Axe (Damage: 20)"; }
};

class Bow : public Weapon {
public:
    int getDamage() const override { return 10; }
    std::string getName() const override { return "Bow (Damage: 10)"; }
};

class Mace : public Weapon {
public:
    int getDamage() const override { return 18; }
    std::string getName() const override { return "Mace (Damage: 18)"; }
};

// --- Armor ---
class Armor {
public:
    virtual int getDefenseBoost() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Armor() = default;
};

class NoArmor : public Armor {
public:
    int getDefenseBoost() const override { return 0; }
    std::string getName() const override { return "No armor"; }
};

class LeatherArmor : public Armor {
public:
    int getDefenseBoost() const override { return 5; }
    std::string getName() const override { return "Leather Armor (Defense: 5)"; }
};

class PlateArmor : public Armor {
public:
    int getDefenseBoost() const override { return 20; }
    std::string getName() const override { return "Plate Armor (Defense: 20)"; }
};

// --- Character ---
class Character {
protected:
    std::string name;
    int baseStrength;
    int baseDefense;
    std::shared_ptr<Weapon> weapon;
    std::shared_ptr<Armor> armor;
public:
    Character(std::string n, int str, int def) : name(n), baseStrength(str), baseDefense(def), weapon(std::make_shared<BasicWeapon>()), armor(std::make_shared<NoArmor>()) {}
    void equipWeapon(std::shared_ptr<Weapon> newWeapon) { weapon = newWeapon; }
    void equipArmor(std::shared_ptr<Armor> newArmor) { armor = newArmor; }
    int getStrength() const { return baseStrength + weapon->getDamage(); }
    int getDefense() const { return baseDefense + armor->getDefenseBoost(); }
    std::string getName() const { return name; }
    std::string getArmorName() const { return armor->getName(); }
    std::string getWeaponName() const { return weapon->getName(); }
};

class Human : public Character {
public:
    Human(std::string n) : Character(n, 20, 10) {}
};

class Troll : public Character {
public:
    Troll(std::string n) : Character(n, 40, 25) {}
};

class Orc : public Character {
public:
    Orc(std::string n) : Character(n, 60, 40) {}
};

// --- Battle System ---
class BattleSystem {
public:
    static void compareCharacters(const Character& hero, const std::vector<std::shared_ptr<Character>>& characters) {
        std::cout << "\nHero: " << hero.getName() << " (Strength: " << hero.getStrength() << ", Defense: " << hero.getDefense() << ")\n";
        std::cout << "Weapon: " << hero.getWeaponName() << ", Armor: " << hero.getArmorName() << "\n";

        for (const auto& opponent : characters) {
            if (opponent->getName() == hero.getName()) continue;
            int damagePerHit = hero.getStrength();
            int neededHits = (opponent->getDefense() + damagePerHit - 1) / damagePerHit;
            std::cout << "Fight against " << opponent->getName() << " (Defense: " << opponent->getDefense() << ") - ";
            std::cout << "Hits needed: " << neededHits << "\n";
        }
    }
};

bool isValidNumber(int& input) {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int getValidatedInput(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (isValidNumber(choice) && choice >= min && choice <= max) {
            return choice;
        }
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
}

int main() {
    std::vector<std::shared_ptr<Character>> characters;

    while (true) {
        std::cout << "\nMenu:\n1. Create a character\n2. Select a character and check battles\n3. Exit\nChoice: ";
        int choice = getValidatedInput(1, 3);

        if (choice == 1) {
            std::string name;
            std::cout << "Enter character name: ";
            std::cin >> name;

            std::cout << "Choose type:\n1. Human (Strength: 20, Defense: 10)\n2. Troll (Strength: 40, Defense: 25)\n3. Orc (Strength: 60, Defense: 40)\n";
            choice = getValidatedInput(1, 3);
            std::shared_ptr<Character> hero;
            switch (choice) {
            case 1: hero = std::make_shared<Human>(name); break;
            case 2: hero = std::make_shared<Troll>(name); break;
            case 3: hero = std::make_shared<Orc>(name); break;
            default: std::cout << "Invalid choice, defaulting to Human.\n"; hero = std::make_shared<Human>(name);
            }

            std::cout << "Choose a weapon:\n1. Sword(+15)\n2. Axe(+20)\n3. Bow(+10)\n4. Mace(+18)\n5. No weapon\n";
            choice = getValidatedInput(1, 5);
            switch (choice) {
            case 1: hero->equipWeapon(std::make_shared<Sword>()); break;
            case 2: hero->equipWeapon(std::make_shared<Axe>()); break;
            case 3: hero->equipWeapon(std::make_shared<Bow>()); break;
            case 4: hero->equipWeapon(std::make_shared<Mace>()); break;
            default: std::cout << "No weapon selected.\n";
            }

            std::cout << "Choose armor:\n1. Leather Armor(+5)\n2. Plate Armor(+20)\n3. No armor\n";
            choice = getValidatedInput(1, 3);
            switch (choice) {
            case 1: hero->equipArmor(std::make_shared<LeatherArmor>()); break;
            case 2: hero->equipArmor(std::make_shared<PlateArmor>()); break;
            default: std::cout << "No armor selected.\n";
            }

            characters.push_back(hero);
            std::cout << "Character " << hero->getName() << " created!\n";
        }

        else if (choice == 2) {
            if (characters.empty()) {
                std::cout << "No characters created!\n";
                continue;
            }

            std::cout << "Select a character:\n";
            for (size_t i = 0; i < characters.size(); ++i) {
                std::cout << i + 1 << ". " << characters[i]->getName() << "\n";
            }
            choice = getValidatedInput(1, characters.size());
            if (choice < 1 || choice > characters.size()) {
                std::cout << "Invalid selection.\n";
                continue;
            }

            BattleSystem::compareCharacters(*characters[choice - 1], characters);
        }
        else if (choice == 3) {
            std::cout << "Exiting...\n";
            break;
        }
        else {
            std::cout << "Invalid choice!\n";
        }
    }
    return 0;
}