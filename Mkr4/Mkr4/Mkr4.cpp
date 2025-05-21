#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Memento — stores the state
class Memento {
    string state;
public:
    Memento(string s) : state(s) {}
    string getState() const { return state; }
};

// Originator — generates random words
class Originator {
    string state;
public:
    void generateWord() {
        vector<string> words = { "hello", "today", "great", "weather", "yes", "no", "maybe", "tomorrow" };
        state = words[rand() % words.size()];
    }

    string getState() const { return state; }

    void setState(const string& s) { state = s; }

    Memento save() const {
        return Memento(state);
    }

    void restore(const Memento& memento) {
        state = memento.getState();
    }
};

// Caretaker — stores the history of states
class Caretaker {
    vector<Memento> history;
public:
    void save(const Memento& m) {
        history.push_back(m);
    }

    Memento undo() {
        if (history.size() < 2) {
            cout << "No previous states to restore!" << endl;
            return history.back();
        }
        history.pop_back(); // remove current state
        return history.back(); // return previous state
    }
};

int main() {
    srand(time(0));

    Originator talker;
    Caretaker memory;

    char choice;

    // Initial word
    talker.generateWord();
    cout << "Spoken word: " << talker.getState() << endl;
    memory.save(talker.save());

    do {
        cout << "Press 'u' to undo, 'n' for next word, 'q' to quit: ";
        cin >> choice;

        if (choice == 'n') {
            talker.generateWord();
            cout << "Spoken word: " << talker.getState() << endl;
            memory.save(talker.save());
        }
        else if (choice == 'u') {
            talker.restore(memory.undo());
            cout << "Reverted to: " << talker.getState() << endl;
        }

    } while (choice != 'q');

    return 0;
}
