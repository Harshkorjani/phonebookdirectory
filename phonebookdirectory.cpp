#include<iostream>
#include<string>
using namespace std;

class TrieNode {
public:
    char data;
    TrieNode**children;
    bool isTerminal;
    string contactName; // Store the name associated with the phone number

    TrieNode(char data) {
        this->data = data;
        children = new TrieNode*[10]; // Assuming only digits 0-9 are allowed in phone numbers
        for (int i = 0; i < 10; i++) {
            children[i] = NULL;
        }
        isTerminal = false;
    }
};

class PhoneBookTrie {
    TrieNode* root;
public:
    PhoneBookTrie() {
        root = new TrieNode('\0');
    }

    void insertContact(TrieNode* root, string phoneNumber, string contactName) {
        // Base case
        if (phoneNumber.size() == 0) {
            root->isTerminal = true;
            root->contactName = contactName;
            return;
        }

        // Small calculation
        int index = phoneNumber[0] - '0'; // Convert character to integer
        TrieNode* child;
        if (root->children[index] != NULL) {
            child = root->children[index];
        }
        else {
            child = new TrieNode(phoneNumber[0]);
            root->children[index] = child;
        }

        // Recursive call
        insertContact(child, phoneNumber.substr(1), contactName);
    }
    void insertContact(string phoneNumber, string contactName) {
        insertContact(root, phoneNumber, contactName);
    }

    pair<bool, string> searchContact(TrieNode* root, string phoneNumber) {
        // Base case
        if (phoneNumber.size() == 0) {
            if (root->isTerminal == false) {
                return make_pair(false, ""); 
            }
            return make_pair(true, root->contactName);
        }

        
        int index = phoneNumber[0] - '0';
        TrieNode* child;
        if (root->children[index] != NULL) {
            child = root->children[index];
        }
        else {
            return make_pair(false, ""); 
        }

        // Recursive Call
        return searchContact(child, phoneNumber.substr(1));
    }

    pair<bool, string> searchContact(string phoneNumber) {
        return searchContact(root, phoneNumber);
    }

    void removeContact(TrieNode* root, string phoneNumber) {
        // Base case
        if (phoneNumber.size() == 0) {
            root->isTerminal = false;
            root->contactName = "";
            return;
        }

        // Small calculation
        TrieNode* child;
        int index = phoneNumber[0] - '0';
        if (root->children[index] != NULL) {
            child = root->children[index];
        }
        else {
            return;
        }

        // Recursive call
        removeContact(child, phoneNumber.substr(1));

        if (child->isTerminal == false) {
            for (int i = 0; i < 10; i++) {
                if (child->children[i] != NULL) {
                    return;
                }
            }
            delete child;
            root->children[index] = NULL;
        }
    }

    void removeContact(string phoneNumber) {
        removeContact(root, phoneNumber);
    }
};
int main() {
    PhoneBookTrie phoneBook;
    int choice;
    
    do {
        cout << "Phone Book Menu:" << endl;
        cout << "1. Insert Contact" << endl;
        cout << "2. Remove Contact" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string contactN, name;
                cout << "Enter phone number: ";
                cin >> contactN;
                cout << "Enter contact name: ";
                cin >> name;
                phoneBook.insertContact(contactN, name);
                cout << "Contact inserted successfully." << endl;
                break;
            }
            case 2: {
                string contactN;
                cout << "Enter phone number to remove: ";
                cin >> contactN;
                phoneBook.removeContact(contactN);
                cout << "Contact removed successfully." << endl;
                break;
            }
            case 3: {
                string contactN;
                cout << "Enter phone number to search: ";
                cin >> contactN;
                pair<bool, string> result = phoneBook.searchContact(contactN);
                if (result.first) {
                    cout << "Contact found: " << result.second << endl;
                } else {
                    cout << "Contact not found." << endl;
                }
                break;
            }
            case 4: {
                cout << "Exiting the phone book." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;

    } while (choice != 4);

    return 0;
}