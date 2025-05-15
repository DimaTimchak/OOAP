#include <iostream>
#include <memory>
using namespace std;

// Abstract print interface
class IPrintStrategy {
public:
    virtual void print(int pages) = 0;
    virtual ~IPrintStrategy() = default;
};

// Laser printing
class LaserPrinter : public IPrintStrategy {
public:
    void print(int pages) override {
        cout << "Laser printing: " << pages << " pages." << endl;
    }
};

// Color printing
class ColorPrinter : public IPrintStrategy {
public:
    void print(int pages) override {
        cout << "Color printing: " << pages << " pages." << endl;
    }
};

// Plotter printing
class PlotterPrinter : public IPrintStrategy {
public:
    void print(int pages) override {
        cout << "Plotter printing: " << pages << " pages." << endl;
    }
};

// Printer context
class PrinterContext {
private:
    unique_ptr<IPrintStrategy> strategy;
public:
    void setStrategy(bool isColor, bool isLarge) {
        if (isLarge)
            strategy = make_unique<PlotterPrinter>();
        else if (isColor)
            strategy = make_unique<ColorPrinter>();
        else
            strategy = make_unique<LaserPrinter>();
    }

    void printDocument(int pages) {
        if (strategy)
            strategy->print(pages);
        else
            cout << "Print strategy not set." << endl;
    }
};

int main() {
    PrinterContext context;
    bool isColor, isLarge;
    int pages;
    char colorChoice, sizeChoice;

    cout << "Enter the number of pages: ";
    while (!(cin >> pages) || pages <= 0) {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Is color printing needed? (y/n): ";
    cin >> colorChoice;
    isColor = (colorChoice == 'y' || colorChoice == 'Y');

    cout << "Is large-format printing needed? (y/n): ";
    cin >> sizeChoice;
    isLarge = (sizeChoice == 'y' || sizeChoice == 'Y');

    context.setStrategy(isColor, isLarge);
    context.printDocument(pages);

    return 0;
}
