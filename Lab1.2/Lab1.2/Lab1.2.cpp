#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

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

void getUserInput(RectangleChain& chain) {
    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Add and draw a rectangle\n";
        std::cout << "2. Show all rectangles\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";

        std::cin >> choice;

        if (choice == 3) {
            running = false; 
            break;
        }

        if (choice == 1) {
            int x, y, width, height;
            std::cout << "Enter top-left coordinates (x y): ";
            std::cin >> x >> y;
            std::cout << "Enter width and height: ";
            std::cin >> width >> height;

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
