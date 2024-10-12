#include <iostream>
#include <string>
using namespace std;

const int MAX_CONTACTS = 100;

class Contacts {
private:
    string names[MAX_CONTACTS];
    string mobiles[MAX_CONTACTS];
    int contactCount;

    bool isValidNumber(const string& number) {
        if (number.length() != 10 || number[0] == '0') {
            return false;
        }
        for (char c : number) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

public:
    Contacts() : contactCount(0) {}

    void addContact(const string& name, const string& mobile) {
        if (contactCount >= MAX_CONTACTS) {
            cout << "Contact list is full." << endl;
            return;
        }
        if (!isValidNumber(mobile)) {
            cout << "Invalid mobile number. Must be 10 digits and not start with 0." << endl;
            return;
        }
        names[contactCount] = name;
        mobiles[contactCount] = mobile;
        contactCount++;
        cout << "Contact added successfully." << endl;
    }

    void deleteContact(const string& name) {
        int index = -1;
        for (int i = 0; i < contactCount; i++) {
            if (names[i] == name) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Contact not found." << endl;
            return;
        }

        for (int i = index; i < contactCount - 1; i++) {
            names[i] = names[i + 1];
            mobiles[i] = mobiles[i + 1];
        }
        contactCount--;
        cout << "Contact deleted successfully." << endl;
    }

    void editContact(const string& name, const string& newMobile) {
        if (!isValidNumber(newMobile)) {
            cout << "Invalid mobile number. Must be 10 digits and not start with 0." << endl;
            return;
        }

        int index = -1;
        for (int i = 0; i < contactCount; i++) {
            if (names[i] == name) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Contact not found." << endl;
            return;
        }

        mobiles[index] = newMobile;
        cout << "Contact edited successfully." << endl;
    }

    void displayContacts() {
        if (contactCount == 0) {
            cout << "No contacts to display." << endl;
            return;
        }
        for (int i = 0; i < contactCount; i++) {
            cout << "Name: " << names[i] << ", Mobile: " << mobiles[i] << endl;
        }
    }
};

void displayMenu() {
    cout << "1. Add Contact" << endl;
    cout << "2. Delete Contact" << endl;
    cout << "3. Edit Contact" << endl;
    cout << "4. Display Contacts" << endl;
    cout << "5. Exit" << endl;
}

int main() {
    Contacts contacts;
    int choice;
    string name, mobile;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter mobile number: ";
                cin >> mobile;
                contacts.addContact(name, mobile);
                cin.ignore();
                break;
            case 2:
                cout << "Enter name of contact to delete: ";
                getline(cin, name);
                contacts.deleteContact(name);
                break;
            case 3:
                cout << "Enter name of contact to edit: ";
                getline(cin, name);
                cout << "Enter new mobile number: ";
                cin >> mobile;
                contacts.editContact(name, mobile);
                cin.ignore();
                break;
            case 4:
                contacts.displayContacts();
                break;
            case 5:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
