#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class IPerson {
public:
    virtual string getName() const = 0;
    virtual void printInfo() const = 0;
    virtual void changeAddress(const string& newCity, const string& newStreet, const string& newBuilding) = 0;
    virtual ~IPerson() = default;
};

class IAddressBook {
public:
    virtual void addEntry(unique_ptr<IPerson> person) = 0;
    virtual void removeEntry(const string& name) = 0;
    virtual void printEntries() const = 0;
    virtual void changePersonAddress(const string& name, const string& newCity, const string& newStreet, const string& newBuilding) = 0;
    virtual ~IAddressBook() = default;
};

class Address {
    string city;
    string street;
    string building;
public:
    Address(string city, string street, string building)
        : city(city), street(street), building(building) {}

    string getFullAddress() const {
        return city + ", " + street + ", " + building;
    }

    void changeAddress(string newCity, string newStreet, string newBuilding) {
        city = newCity;
        street = newStreet;
        building = newBuilding;
    }
};

class Person : public IPerson {
    string name;
    unique_ptr<Address> address;
public:
    Person(string name, unique_ptr<Address> address)
        : name(name), address(move(address)) {}

    string getName() const override { return name; }

    void printInfo() const override {
        cout << "Name: " << name << ", Address: " << address->getFullAddress() << endl;
    }

    void changeAddress(const string& newCity, const string& newStreet, const string& newBuilding) override {
        address->changeAddress(newCity, newStreet, newBuilding);
    }
};


class AddressBookManager {
public:
    void addEntry(vector<unique_ptr<IPerson>>& entries, unique_ptr<IPerson> person) {
        entries.push_back(move(person));
    }

    void removeEntry(vector<unique_ptr<IPerson>>& entries, const string& name) {
        auto it = remove_if(entries.begin(), entries.end(),
            [&name](const unique_ptr<IPerson>& person) { return person->getName() == name; });
        if (it != entries.end()) {
            entries.erase(it, entries.end());
            cout << "Entry for " << name << " removed.\n";
        }
        else {
            cout << "Entry for " << name << " not found.\n";
        }
    }

    void printEntries(const vector<unique_ptr<IPerson>>& entries) const {
        for (const auto& person : entries) {
            person->printInfo();
        }
    }

    IPerson* findPerson(vector<unique_ptr<IPerson>>& entries, const string& name) {
        for (auto& person : entries) {
            if (person->getName() == name) {
                return person.get();
            }
        }
        return nullptr;
    }
};

class AddressBook : public IAddressBook {
    vector<unique_ptr<IPerson>> entries;
    AddressBookManager manager;
public:
    void addEntry(unique_ptr<IPerson> person) override {
        manager.addEntry(entries, move(person));
    }

    void removeEntry(const string& name) override {
        manager.removeEntry(entries, name);
    }

    void printEntries() const override {
        manager.printEntries(entries);
    }

    void changePersonAddress(const string& name, const string& newCity, const string& newStreet, const string& newBuilding) override {
        IPerson* person = manager.findPerson(entries, name);
        if (person) {
            person->changeAddress(newCity, newStreet, newBuilding);
            cout << "Address for " << name << " changed.\n";
        }
        else {
            cout << "Person not found.\n";
        }
    }
};

int main() {
    unique_ptr<IAddressBook> addressBook = make_unique<AddressBook>();

    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add entry\n";
        cout << "2. Remove entry\n";
        cout << "3. Print all entries\n";
        cout << "4. Change address\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, city, street, building;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter city: ";
            cin >> city;
            cout << "Enter street: ";
            cin >> street;
            cout << "Enter building: ";
            cin >> building;

            unique_ptr<Address> address = make_unique<Address>(city, street, building);
            unique_ptr<IPerson> person = make_unique<Person>(name, move(address));
            addressBook->addEntry(move(person));
            cout << "Entry added.\n";
            break;
        }
        case 2: {
            string name;
            cout << "Enter name to remove: ";
            cin >> name;
            addressBook->removeEntry(name);
            break;
        }
        case 3: {
            addressBook->printEntries();
            break;
        }
        case 4: {
            string name, newCity, newStreet, newBuilding;
            cout << "Enter name to change address: ";
            cin >> name;

            cout << "Enter new city: ";
            cin >> newCity;
            cout << "Enter new street: ";
            cin >>newStreet;
            cout << "Enter new building: ";
            cin >> newBuilding;

            addressBook->changePersonAddress(name, newCity, newStreet, newBuilding);
            break;
        }
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
