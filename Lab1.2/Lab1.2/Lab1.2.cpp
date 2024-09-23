#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <limits> // для std::numeric_limits

std::atomic<bool> running(true);
int choice;

class Rectangle {
private:
    const int x, y;
    const int width, height;

public:
    Rectangle(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Green);
        window.draw(rectangle);
    }
};

class RectangleChain {
private:
    std::vector<Rectangle> rectangles;

public:
    void addRectangle(const Rectangle& rect) {
        rectangles.push_back(rect);
    }

    void drawAll(sf::RenderWindow& window) const {
        for (const auto& rect : rectangles) {
            rect.draw(window);
        }
    }

    const Rectangle& getLastRectangle() const {
        return rectangles.back();
    }

    bool hasRectangles() const {
        return !rectangles.empty();
    }
};

void clearInputStream() {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void getUserInput(RectangleChain& chain) {
    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Add and draw a rectangle\n";
        std::cout << "2. Show all rectangles\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input! Please enter a number.\n";
            clearInputStream();
            continue; 
        }

        if (choice == 3) {
            running = false;
            break;
        }

        if (choice == 1) {
            int x, y, width, height;

            bool validInput = false;
            while (!validInput) {
                std::cout << "Enter top-left coordinates (x y): ";
                std::cin >> x >> y;

                if (std::cin.fail()) {
                    std::cout << "Invalid input! Please enter valid numbers for coordinates.\n";
                    clearInputStream();
                    continue; 
                }

                if (x < 0 || x > 800 || y < 0 || y > 600) {
                    std::cout << "Invalid coordinates! X must be between 0 and 800, Y between 0 and 600.\n";
                    continue;
                }

                std::cout << "Enter width and height: ";
                std::cin >> width >> height;

                if (std::cin.fail()) {
                    std::cout << "Invalid input! Please enter valid numbers for width and height.\n";
                    clearInputStream();
                    continue; 
                }

                if (width <= 0 || height <= 0 || x + width > 800 || y + height > 600) {
                    std::cout << "Invalid dimensions! Width and height must be positive and within window bounds.\n";
                    continue;
                }

                validInput = true;              }

            Rectangle rect(x, y, width, height);
            chain.addRectangle(rect);
        }
    }
}

void renderWindow(sf::RenderWindow& window, RectangleChain& chain) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                running = false;
            }
        }

        window.clear();

        if (choice == 2) {
            chain.drawAll(window);
        }
        else if (choice == 1) {
            if (chain.hasRectangles()) {
                chain.getLastRectangle().draw(window);
            }
        }

        window.display();

        if (!running) {
            break;
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rectangle Chain");
    RectangleChain chain;

    std::thread inputThread(getUserInput, std::ref(chain));

    renderWindow(window, chain);

    inputThread.join();

    return 0;
}
