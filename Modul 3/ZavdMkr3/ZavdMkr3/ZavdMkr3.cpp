#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cctype>
#include <algorithm> // for std::all_of

using namespace std;

// Context stores the input string and the parsed date components
class Context {
public:
    string input;
    int day = 0, month = 0, year = 0;

    Context(const string& input) : input(input) {}
};

// Abstract expression
class DateExpression {
public:
    virtual bool interpret(Context& context) = 0; // returns true if parsed successfully
    virtual ~DateExpression() = default;
};

// Helper to check if a string is numeric
bool isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

// Helper to check valid date with leap year support
bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || day < 1) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    // Leap year check for February
    if (month == 2 &&
        ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return day <= 29;
    }

    return day <= daysInMonth[month - 1];
}

// MM-DD-YYYY parser
class MMDDYYYYExpression : public DateExpression {
public:
    bool interpret(Context& context) override {
        stringstream ss(context.input);
        string mm, dd, yyyy;
        getline(ss, mm, '-');
        getline(ss, dd, '-');
        getline(ss, yyyy);

        if (!isNumber(mm) || !isNumber(dd) || !isNumber(yyyy)) return false;

        context.month = stoi(mm);
        context.day = stoi(dd);
        context.year = stoi(yyyy);

        return isValidDate(context.day, context.month, context.year);
    }
};

// DD-MM-YYYY parser
class DDMMYYYYExpression : public DateExpression {
public:
    bool interpret(Context& context) override {
        stringstream ss(context.input);
        string dd, mm, yyyy;
        getline(ss, dd, '-');
        getline(ss, mm, '-');
        getline(ss, yyyy);

        if (!isNumber(dd) || !isNumber(mm) || !isNumber(yyyy)) return false;

        context.day = stoi(dd);
        context.month = stoi(mm);
        context.year = stoi(yyyy);

        return isValidDate(context.day, context.month, context.year);
    }
};

// YYYY-MM-DD parser
class YYYYMMDDExpression : public DateExpression {
public:
    bool interpret(Context& context) override {
        stringstream ss(context.input);
        string yyyy, mm, dd;
        getline(ss, yyyy, '-');
        getline(ss, mm, '-');
        getline(ss, dd);

        if (!isNumber(yyyy) || !isNumber(mm) || !isNumber(dd)) return false;

        context.year = stoi(yyyy);
        context.month = stoi(mm);
        context.day = stoi(dd);

        return isValidDate(context.day, context.month, context.year);
    }
};

// Detects format and returns correct interpreter
unique_ptr<DateExpression> getExpression(const string& input) {
    if (input.length() < 8) return nullptr;

    if (isdigit(input[0]) && input[4] == '-' && input[7] == '-') {
        // Format: YYYY-MM-DD
        return make_unique<YYYYMMDDExpression>();
    }
    else if (isdigit(input[0]) && isdigit(input[1]) && input[2] == '-' &&
        isdigit(input[3]) && isdigit(input[4]) && input[5] == '-') {
        // Format: MM-DD-YYYY or DD-MM-YYYY
        int first = stoi(input.substr(0, 2));
        int second = stoi(input.substr(3, 2));

        if (first > 12 && second <= 12)
            return make_unique<DDMMYYYYExpression>();
        else if (first <= 12 && second > 12)
            return make_unique<MMDDYYYYExpression>();
        else
            return make_unique<MMDDYYYYExpression>(); // default fallback
    }

    return nullptr;
}

// Main program
int main() {
    string input;
    cout << "Enter a date (MM-DD-YYYY, DD-MM-YYYY, or YYYY-MM-DD): ";
    getline(cin, input); // safer than cin >> input

    Context context(input);
    auto expression = getExpression(input);

    if (expression && expression->interpret(context)) {
        cout << "\nParsed date:\n";
        cout << "  Day:   " << context.day << "\n";
        cout << "  Month: " << context.month << "\n";
        cout << "  Year:  " << context.year << "\n";
    }
    else {
        cout << "\nInvalid date or unsupported format.\n";
    }

    return 0;
}
