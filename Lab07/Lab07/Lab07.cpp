#include <iostream>
#include <vector>
#include <memory>
#include <string>

// ===== Receiver =====
class FastFood {
public:
    void addOrder(const std::string& item) {
        orders.push_back(item);
        std::cout << "Added: " << item << "\n";
    }

    void removeOrderByIndex(size_t index) {
        if (index < orders.size()) {
            std::cout << "Removed: " << orders[index] << "\n";
            orders.erase(orders.begin() + index);
        }
        else {
            std::cout << "Invalid order number!\n";
        }
    }

    void showOrders() const {
        std::cout << "\n Current Orders:\n";
        if (orders.empty()) {
            std::cout << " - (none)\n";
        }
        else {
            for (size_t i = 0; i < orders.size(); ++i) {
                std::cout << " " << i + 1 << ") " << orders[i] << "\n";
            }
        }
        std::cout << "\n";
    }

    size_t getOrderCount() const {
        return orders.size();
    }

private:
    std::vector<std::string> orders;
};

// ===== Command Interface =====
class OrderCommand {
public:
    virtual ~OrderCommand() = default;
    virtual void execute() = 0;
};

// ===== Concrete Commands =====
class AddOrderCommand : public OrderCommand {
public:
    AddOrderCommand(FastFood& receiver, const std::string& item)
        : receiver(receiver), item(item) {}

    void execute() override {
        receiver.addOrder(item);
    }

private:
    FastFood& receiver;
    std::string item;
};

class RemoveOrderCommand : public OrderCommand {
public:
    RemoveOrderCommand(FastFood& receiver, size_t index)
        : receiver(receiver), index(index) {}

    void execute() override {
        receiver.removeOrderByIndex(index);
    }

private:
    FastFood& receiver;
    size_t index;
};

// ===== Invoker =====
class OrderInvoker {
public:
    void setCommand(std::unique_ptr<OrderCommand> cmd) {
        command = std::move(cmd);
    }

    void runCommand() {
        if (command) command->execute();
    }

private:
    std::unique_ptr<OrderCommand> command;
};

// Допоміжна функція для безпечного зчитування числа
int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear(); // очистити стан потоку
            std::cin.ignore(10000, '\n'); // пропустити залишки вводу
            std::cout << " Invalid input! Please enter a valid number.\n";
        }
        else {
            std::cin.ignore(10000, '\n'); // очистити буфер після числа
            return value;
        }
    }
}

// ===== Menu-Driven Client =====
int main() {
    FastFood fastFood;
    OrderInvoker invoker;

    std::vector<std::string> menu = {
        "Burger", "Fries", "Hot Dog", "Pizza", "Drink"
    };

    int choice;
    do {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Place an order\n";
        std::cout << "2. View current orders\n";
        std::cout << "3. Remove an order\n";
        std::cout << "4. Exit\n";
        choice = getIntInput("Enter your choice: ", 1, 4);

        switch (choice) {
        case 1: {
            std::cout << "\n Food Menu:\n";
            for (size_t i = 0; i < menu.size(); ++i) {
                std::cout << " " << i + 1 << ") " << menu[i] << "\n";
            }
            size_t itemChoice = getIntInput("Choose an item (number): ", 1, static_cast<int>(menu.size()));
            invoker.setCommand(std::make_unique<AddOrderCommand>(fastFood, menu[itemChoice - 1]));
            invoker.runCommand();
            break;
        }

        case 2:
            fastFood.showOrders();
            break;

        case 3: {
            fastFood.showOrders();
            if (fastFood.getOrderCount() == 0) break;

            size_t removeIndex = getIntInput("Enter the order number to remove: ", 1, static_cast<int>(fastFood.getOrderCount()));
            invoker.setCommand(std::make_unique<RemoveOrderCommand>(fastFood, removeIndex - 1));
            invoker.runCommand();
            break;
        }

        case 4:
            std::cout << "👋 Goodbye!\n";
            break;
        }
    } while (choice != 4);
    return 0;
}
