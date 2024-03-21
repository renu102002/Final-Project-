#include <iostream>
#include <string>

using namespace std;

// Define a class for users
//asset tracking
class User {
private:
    string name;

public:
    User(const string& name) : name(name) {}

    // Getter method
    string getName() const { return name; }
};

// Define a class for assets
class Asset {
private:
    string name;
    string location;
    User* owner;
    double value; // Value of the asset

public:
    Asset(const string& name, const string& location, User* owner, double value) : name(name), location(location), owner(owner), value(value) {}

    // Getter methods
    string getName() const { return name; }
    string getLocation() const { return location; }
    User* getOwner() const { return owner; }
    double getValue() const { return value; }

    // Setter method for modifying location
    void setLocation(const string& newLocation) {
        location = newLocation;
    }

    // Method to display asset details
    void display() const {
        cout << "Name: " << name << ", Location: " << location << ", Value: " << value << ", Owner: " << owner->getName() << endl;
    }
};

// Define a linked list node for Asset
struct AssetNode {
    Asset asset;
    AssetNode* next;

    AssetNode(const Asset& asset) : asset(asset), next(nullptr) {}
};

// Define a linked list node for User
struct UserNode {
    User user;
    UserNode* next;

    UserNode(const User& user) : user(user), next(nullptr) {}
};

// Asset Tracker class to manage assets and users using linked lists
class AssetTracker {
private:
    UserNode* usersHead;
    AssetNode* assetsHead;

public:
    AssetTracker() : usersHead(nullptr), assetsHead(nullptr) {}

    // Method to add a user
    void addUser(const User& user) {
        UserNode* newNode = new UserNode(user);
        newNode->next = usersHead;
        usersHead = newNode;
    }

    // Method to add an asset
    void addAsset(const Asset& asset) {
        AssetNode* newNode = new AssetNode(asset);
        newNode->next = assetsHead;
        assetsHead = newNode;
    }

    // Method to display all assets
    void displayAllAssets() const {
        cout << "---- All Assets ----" << endl;
        AssetNode* current = assetsHead;
        while (current != nullptr) {
            current->asset.display();
            current = current->next;
        }
        cout << "---------------------" << endl;
    }

    // Method to search for an asset by name
    void searchAssetByName(const string& name) const {
        bool found = false;
        cout << "---- Search Results ----" << endl;
        AssetNode* current = assetsHead;
        while (current != nullptr) {
            if (current->asset.getName() == name) {
                current->asset.display();
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Asset with name '" << name << "' not found." << endl;
        }
        cout << "-------------------------" << endl;
    }

    // Method to get the head of users list (for demonstration purposes)
    UserNode* getUsersHead() const {
        return usersHead;
    }

    // Method to calculate total net worth of the owner
    double calculateTotalNetWorth(const User& user) const {
        double totalNetWorth = 0;
        AssetNode* current = assetsHead;
        while (current != nullptr) {
            if (current->asset.getOwner() == &user) {
                totalNetWorth += current->asset.getValue();
            }
            current = current->next;
        }
        return totalNetWorth;
    }
};

int main() {
    AssetTracker tracker;

    int choice;
    string assetName, ownerName, location;
    double assetValue;

    do {
        cout << "------ Asset Tracking System ------" << endl;
        cout << "1. Add Asset\n2. Display All Assets\n3. Search Asset by Name\n4. Calculate Owner's Total Net Worth\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter asset name: ";
            cin >> assetName;
            cout << "Enter owner name: ";
            cin >> ownerName;
            cout << "Enter location: ";
            cin >> location;
            cout << "Enter asset value: ";
            cin >> assetValue;

            // Check if the owner already exists
            User* owner = nullptr;
            UserNode* currentUser = tracker.getUsersHead();
            while (currentUser != nullptr) {
                if (currentUser->user.getName() == ownerName) {
                    owner = &currentUser->user;
                    break;
                }
                currentUser = currentUser->next;
            }

            // If owner doesn't exist, create a new one
            if (!owner) {
                owner = new User(ownerName);
                tracker.addUser(*owner);
            }

            // Create and add asset
            tracker.addAsset(Asset(assetName, location, owner, assetValue));
            cout << "Asset added successfully." << endl;
            break;
        }
        case 2:
            tracker.displayAllAssets();
            break;
        case 3:
            cout << "Enter asset name to search: ";
            cin >> assetName;
            tracker.searchAssetByName(assetName);
            break;
        case 4: {
            cout << "Enter owner name: ";
            cin >> ownerName;

            // Check if the owner exists
            User* owner = nullptr;
            UserNode* currentUser = tracker.getUsersHead();
            while (currentUser != nullptr) {
                if (currentUser->user.getName() == ownerName) {
                    owner = &currentUser->user;
                    break;
                }
                currentUser = currentUser->next;
            }

            if (owner) {
                double totalNetWorth = tracker.calculateTotalNetWorth(*owner);
                cout << "Total net worth of owner " << ownerName << ": " << totalNetWorth << endl;
            }
            else {
                cout << "Owner with name '" << ownerName << "' not found." << endl;
            }
            break;
        }
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}