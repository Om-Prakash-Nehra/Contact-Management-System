#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string mobile;
    Contact* next;
};

class Contacts {
private:
    Contact* head;

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
    Contacts() : head(nullptr) {}

    void addContact(const string& name, const string& mobile) {
        if (!isValidNumber(mobile)) {
            cout << "Invalid mobile number. Must be 10 digits and not start with 0." << endl;
            return;
        }
        Contact* newContact = new Contact{name, mobile, head};
        head = newContact;
        cout << "Contact added successfully." << endl;
    }

    void deleteContact(const string& name) {
        Contact* current = head;
        Contact* previous = nullptr;

        while (current != nullptr && current->name != name) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Contact not found." << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Contact deleted successfully." << endl;
    }

    void editContact(const string& name, const string& newMobile) {
        if (!isValidNumber(newMobile)) {
            cout << "Invalid mobile number. Must be 10 digits and not start with 0." << endl;
            return;
        }

        Contact* current = head;
        while (current != nullptr && current->name != name) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Contact not found." << endl;
            return;
        }

        current->mobile = newMobile;
        cout << "Contact edited successfully." << endl;
    }

    void displayContacts() {
        Contact* current = head;
        if (current == nullptr) {
            cout << "No contacts to display." << endl;
            return;
        }
        while (current != nullptr) {
            cout << "Name: " << current->name << ", Mobile: " << current->mobile << endl;
            current = current->next;
        }
    }

    ~Contacts() {
        while (head != nullptr) {
            Contact* temp = head;
            head = head->next;
            delete temp;
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

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter mobile number: ";
                cin >> mobile;
                contacts.addContact(name, mobile);
                break;
            case 2:
                cout << "Enter name of contact to delete: ";
                cin >> name;
                contacts.deleteContact(name);
                break;
            case 3:
                cout << "Enter name of contact to edit: ";
                cin >> name;
                cout << "Enter new mobile number: ";
                cin >> mobile;
                contacts.editContact(name, mobile);
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
