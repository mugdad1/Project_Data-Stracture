#include <iostream>
#include <string>
using namespace std;

// Part Structure
struct Part {
    string name;
    string memory;
    string code;
    float price;
    string ManufacturerName;
    Part* next_part;

    Part(string name, string memory, string code, float price, string ManufacturerName)
        : name(name), memory(memory), code(code), price(price), ManufacturerName(ManufacturerName), next_part(nullptr) {}
};

// Manufacturer Structure
struct Manufacturer {
    string name;
    string phone;
    string address;
    string Email;
    Part* parts;
    Manufacturer* next_manufactrer;

    Manufacturer(string name, string phone, string address, string Email)
        : name(name), phone(phone), address(address), Email(Email), parts(nullptr), next_manufactrer(nullptr) {}
};

// Manage Parts and Manufacturers in separate lists
class InventoryManager {
private:
    Part* part_head;
    Part* part_tail;
    Manufacturer* manufacturer_head;
    Manufacturer* manufacturer_tail;

public:
    InventoryManager() : part_head(nullptr), part_tail(nullptr), manufacturer_head(nullptr), manufacturer_tail(nullptr) {}

    // Add a new Part
    void addPart() {
        string name, memory, code, ManufacturerName;
        float price;

        cout << "Enter the Part Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter the Part Memory: ";
        getline(cin, memory);

        cout << "Enter the Part Code: ";
        getline(cin, code);

        cout << "Enter the Part Price: ";
        cin >> price;

        cout << "Enter the Part Manufacturer: ";
        cin.ignore();
        getline(cin, ManufacturerName);

        Part* newPart = new Part(name, memory, code, price, ManufacturerName);

        if (!part_head) {
            part_head = part_tail = newPart;
        } else {
            part_tail->next_part = newPart;
            part_tail = newPart;
        }
        cout << "Part added successfully.\n";
    }

    // Add a new Manufacturer
    void addManufacturer() {
        string name, phone, address, Email;

        cout << "Enter Manufacturer Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Manufacturer Phone: ";
        getline(cin, phone);

        cout << "Enter Manufacturer Address: ";
        getline(cin, address);

        cout << "Enter Manufacturer Email: ";
        getline(cin, Email);

        Manufacturer* newManufacturer = new Manufacturer(name, phone, address, Email);

        if (!manufacturer_head) {
            manufacturer_head = manufacturer_tail = newManufacturer;
        } else {
            manufacturer_tail->next_manufactrer = newManufacturer;
            manufacturer_tail = newManufacturer;
        }
        cout << "Manufacturer added successfully.\n";
    }

    // Display Parts List
    void displayParts() {
        Part* part_temp = part_head;
        if (!part_temp) {
            cout << "No parts available.\n";
        } else {
            cout << "Displaying Parts List:\n";
            while (part_temp) {
                cout << "Part Name: " << part_temp->name << "\n";
                cout << "Memory: " << part_temp->memory << "\n";
                cout << "Code: " << part_temp->code << "\n";
                cout << "Price: " << part_temp->price << "\n";
                cout << "Manufacturer: " << part_temp->ManufacturerName << "\n";
                cout << "----------------------------------------\n";
                part_temp = part_temp->next_part;
            }
        }
    }

    // Display Manufacturers List
    void displayManufacturers() {
        Manufacturer* manufacturer_temp = manufacturer_head;
        if (!manufacturer_temp) {
            cout << "No manufacturers available.\n";
        } else {
            cout << "Displaying Manufacturers List:\n";
            while (manufacturer_temp) {
                cout << "Manufacturer Name: " << manufacturer_temp->name << "\n";
                cout << "Phone: " << manufacturer_temp->phone << "\n";
                cout << "Address: " << manufacturer_temp->address << "\n";
                cout << "Email: " << manufacturer_temp->Email << "\n";
                cout << "----------------------------------------\n";
                manufacturer_temp = manufacturer_temp->next_manufactrer;
            }
        }
    }

    // Assign Part to Manufacturer
    void assignPartToManufacturer() {
        string partCode, manufacturerName;

        cout << "Enter the Part Code to assign: ";
        cin >> partCode;

        Part* part_temp = findPart(partCode);
        if (!part_temp) {
            cout << "Part not found.\n";
            return;
        }

        cout << "Enter Manufacturer Name to assign the part: ";
        cin.ignore();
        getline(cin, manufacturerName);

        Manufacturer* manufacturer_temp = findManufacturer(manufacturerName);
        if (!manufacturer_temp) {
            cout << "Manufacturer not found.\n";
            return;
        }

        part_temp->next_part = manufacturer_temp->parts;
        manufacturer_temp->parts = part_temp;

        cout << "Part assigned to Manufacturer successfully.\n";
    }

    // Remove Part from Manufacturer
    void removePartFromManufacturer() {
        string partCode, manufacturerName;

        cout << "Enter the Part Code to remove from Manufacturer: ";
        cin >> partCode;

        Part* part_temp = findPart(partCode);
        if (!part_temp) {
            cout << "Part not found.\n";
            return;
        }

        cout << "Enter Manufacturer Name to remove the part from: ";
        cin.ignore();
        getline(cin, manufacturerName);

        Manufacturer* manufacturer_temp = findManufacturer(manufacturerName);
        if (!manufacturer_temp) {
            cout << "Manufacturer not found.\n";
            return;
        }

        Part* prev_part = nullptr;
        Part* cur_part = manufacturer_temp->parts;

        while (cur_part) {
            if (cur_part->code == partCode) {
                if (prev_part) {
                    prev_part->next_part = cur_part->next_part;
                } else {
                    manufacturer_temp->parts = cur_part->next_part;
                }
                delete cur_part;
                cout << "Part removed from Manufacturer successfully.\n";
                return;
            }
            prev_part = cur_part;
            cur_part = cur_part->next_part;
        }

        cout << "Part not associated with Manufacturer.\n";
    }

    // Update Part
    void updatePart() {
        string partCode;

        cout << "Enter the Part Code to update: ";
        cin >> partCode;

        Part* part_temp = findPart(partCode);
        if (!part_temp) {
            cout << "Part not found.\n";
            return;
        }

        cout << "Enter updated Part Name: ";
        cin.ignore();
        getline(cin, part_temp->name);

        cout << "Enter updated Part Memory: ";
        getline(cin, part_temp->memory);

        cout << "Enter updated Part Price: ";
        cin >> part_temp->price;

        cout << "Part updated successfully.\n";
    }

    // Update Manufacturer
    void updateManufacturer() {
        string manufacturerName;

        cout << "Enter the Manufacturer Name to update: ";
        cin.ignore();
        getline(cin, manufacturerName);

        Manufacturer* manufacturer_temp = findManufacturer(manufacturerName);
        if (!manufacturer_temp) {
            cout << "Manufacturer not found.\n";
            return;
        }

        cout << "Enter updated Manufacturer Phone: ";
        getline(cin, manufacturer_temp->phone);

        cout << "Enter updated Manufacturer Address: ";
        getline(cin, manufacturer_temp->address);

        cout << "Enter updated Manufacturer Email: ";
        getline(cin, manufacturer_temp->Email);

        cout << "Manufacturer updated successfully.\n";
    }

    // Delete Part
    void deletePart() {
        string partCode;

        cout << "Enter the Part Code to delete: ";
        cin >> partCode;

        Part* prev_part = nullptr;
        Part* part_temp = part_head;

        while (part_temp) {
            if (part_temp->code == partCode) {
                if (prev_part) {
                    prev_part->next_part = part_temp->next_part;
                } else {
                    part_head = part_temp->next_part;
                }
                delete part_temp;
                cout << "Part deleted successfully.\n";
                return;
            }
            prev_part = part_temp;
            part_temp = part_temp->next_part;
        }

        cout << "Part not found.\n";
    }

    // Delete Manufacturer
    void deleteManufacturer() {
        string manufacturerName;

        cout << "Enter the Manufacturer Name to delete: ";
        cin.ignore();
        getline(cin, manufacturerName);

        Manufacturer* prev_manufacturer = nullptr;
        Manufacturer* manufacturer_temp = manufacturer_head;

        while (manufacturer_temp) {
            if (manufacturer_temp->name == manufacturerName) {
                if (prev_manufacturer) {
                    prev_manufacturer->next_manufactrer = manufacturer_temp->next_manufactrer;
                } else {
                    manufacturer_head = manufacturer_temp->next_manufactrer;
                }
                delete manufacturer_temp;
                cout << "Manufacturer deleted successfully.\n";
                return;
            }
            prev_manufacturer = manufacturer_temp;
            manufacturer_temp = manufacturer_temp->next_manufactrer;
        }

        cout << "Manufacturer not found.\n";
    }

    // Search Part Details by Code
    void searchPartDetails() {
        string partCode;

        cout << "Enter the Part Code to search: ";
        cin >> partCode;

        Part* part_temp = findPart(partCode);
        if (part_temp) {
            cout << "Part Name: " << part_temp->name << "\n";
            cout << "Memory: " << part_temp->memory << "\n";
            cout << "Price: " << part_temp->price << "\n";
            cout << "Manufacturer: " << part_temp->ManufacturerName << "\n";
        } else {
            cout << "Part not found.\n";
        }
    }

    // Search Manufacturer Details by Name
    void searchManufacturerDetails() {
        string manufacturerName;

        cout << "Enter the Manufacturer Name to search: ";
        cin.ignore();
        getline(cin, manufacturerName);

        Manufacturer* manufacturer_temp = findManufacturer(manufacturerName);
        if (manufacturer_temp) {
            cout << "Manufacturer Name: " << manufacturer_temp->name << "\n";
            cout << "Phone: " << manufacturer_temp->phone << "\n";
            cout << "Address: " << manufacturer_temp->address << "\n";
            cout << "Email: " << manufacturer_temp->Email << "\n";
        } else {
            cout << "Manufacturer not found.\n";
        }
    }

    // Helper function to find a part by code
    Part* findPart(const string& code) {
        Part* part_temp = part_head;
        while (part_temp) {
            if (part_temp->code == code) {
                return part_temp;
            }
            part_temp = part_temp->next_part;
        }
        return nullptr;
    }

    // Helper function to find a manufacturer by name
    Manufacturer* findManufacturer(const string& name) {
        Manufacturer* manufacturer_temp = manufacturer_head;
        while (manufacturer_temp) {
            if (manufacturer_temp->name == name) {
                return manufacturer_temp;
            }
            manufacturer_temp = manufacturer_temp->next_manufactrer;
        }
        return nullptr;
    }
};

// Main Function
int main() {
    InventoryManager manager;
    int choice;

    do {
        cout << "\nComputer Parts Management Services:\n";
        cout << "------------------------------------\n";
        cout << "1) Add new Part\n";
        cout << "2) Add new Manufacturer\n";
        cout << "3) Display Parts List\n";
        cout << "4) Display Manufacturer List\n";
        cout << "5) Assign Part To Manufacturer\n";
        cout << "6) Remove Part From Manufacturer\n";
        cout << "7) Update Part\n";
        cout << "8) Update Manufacturer\n";
        cout << "9) Delete Part\n";
        cout << "10) Delete Manufacturer\n";
        cout << "11) Search Part Details by Code\n";
        cout << "12) Search Manufacturer Details by Name\n";
        cout << "13) Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addPart(); break;
            case 2: manager.addManufacturer(); break;
            case 3: manager.displayParts(); break;
            case 4: manager.displayManufacturers(); break;
            case 5: manager.assignPartToManufacturer(); break;
            case 6: manager.removePartFromManufacturer(); break;
            case 7: manager.updatePart(); break;
            case 8: manager.updateManufacturer(); break;
            case 9: manager.deletePart(); break;
            case 10: manager.deleteManufacturer(); break;
            case 11: manager.searchPartDetails(); break;
            case 12: manager.searchManufacturerDetails(); break;
            case 13: cout << "Exiting...\n"; break;
            
            default: cout << "Invalid option, please try again.\n"; break;
        }
    } while (choice != 13);

    return 0;
}
