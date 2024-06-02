#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item {
public:
    string name;
    int damage;
    int durability;
    string rarity;

    Item(string name, int damage = 0, int durability = 100, string rarity = "common")
        : name{name}, damage{damage}, durability{durability}, rarity{rarity} {}
};

class Equipment {
    Item*** grid;
    int rows;
    int cols;
public:
    Equipment(int rows = 5, int cols = 5) : rows{rows}, cols{cols} {
        grid = new Item**[rows];
        for(int i = 0; i < rows; i++) {
            grid[i] = new Item*[cols];
        }
        int count = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                grid[i][j] = new Item("item " + to_string(count));
                count++;
            }
        }
    }
    ~Equipment() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                delete grid[i][j];
            }
        }
        for(int i = 0; i < rows; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
    void display() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(grid[i][j] != nullptr) {
                    cout << "[" << grid[i][j]->name << "]\t";
                } else {
                    cout << "[Empty]\t";
                }
            }
            cout << endl;
        }
    }
    bool isValidPosition(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
    void swapItems(int row1, int col1, int row2, int col2) {
        if (!isValidPosition(row1, col1) || !isValidPosition(row2, col2)) {
            cout << "Invalid positions!" << endl;
            return;
        }

        Item* temp = grid[row1][col1];
        grid[row1][col1] = grid[row2][col2];
        grid[row2][col2] = temp;
    }
    void deleteItem(int row, int col) {
        if (!isValidPosition(row, col)) {
            cout << "Invalid position!" << endl;
            return;
        }

        delete grid[row][col];
        grid[row][col] = nullptr;
    }
    Item* getItem(int row, int col) {
        if(!isValidPosition(row,col)) {
            return nullptr;
        }

        return grid[row][col];
    }
    void resizeEquipment(int newRows, int newCols) {
        Item*** newGrid = new Item**[newRows];
        for(int i = 0; i < newRows; i++) {
            newGrid[i] = new Item*[newCols];
        }

        for(int i = 0; i < newRows; i++) {
            for(int j = 0; j < newCols; j++) {
                if(i < rows && j < cols) {
                    newGrid[i][j] = grid[i][j];
                } else {
                    newGrid[i][j] = nullptr;
                }
            }
        }

        for(int i = 0; i < rows; i++) {
            delete[] grid[i];
        }
        delete[] grid;

        grid = newGrid;
        rows = newRows;
        cols = newCols;
    }
    void addItem(int row, int col, const string& itemName) {
        if (!isValidPosition(row, col)) {
            cout << "Invalid position!" << endl;
            return;
        }

        if(grid[row][col] != nullptr) {
            delete grid[row][col];
        }
        grid[row][col] = new Item(itemName);
    }
    void displayItemStats(int row, int col) {
        if (!isValidPosition(row, col) || grid[row][col] == nullptr) {
            cout << "No item at this position!" << endl;
            return;
        }

        Item* item = grid[row][col];
        cout << "Name: " << item->name << endl;
        cout << "Damage: " << item->damage << endl;
        cout << "Durability: " << item->durability << endl;
        cout << "Rarity: " << item->rarity << endl;
    }
};

class Player {
    int gold;
    Equipment equipment;
    Item* armor;
    Item* trousers;
    Item* boots;
    Item* mainWeapon;
    Item* sideWeapon;

public:
    Player() : gold{0}, armor{nullptr}, trousers{nullptr}, boots{nullptr}, mainWeapon{nullptr}, sideWeapon{nullptr} {}

    void displayEquipment() {
        cout << "Gold: " << gold << endl;
        cout << "Armor: " << (armor ? armor->name : "None") << endl;
        cout << "Trousers: " << (trousers ? trousers->name : "None") << endl;
        cout << "Boots: " << (boots ? boots->name : "None") << endl;
        cout << "Main Weapon: " << (mainWeapon ? mainWeapon->name : "None") << endl;
        cout << "Side Weapon: " << (sideWeapon ? sideWeapon->name : "None") << endl;
        cout << "\nInventory:\n";
        equipment.display();
    }

    void equipArmor(int row, int col) { armor = equipment.getItem(row, col); }
    void equipTrousers(int row, int col) { trousers = equipment.getItem(row, col); }
    void equipBoots(int row, int col) { boots = equipment.getItem(row, col); }
    void equipMainWeapon(int row, int col) { mainWeapon = equipment.getItem(row, col); }
    void equipSideWeapon(int row, int col) { sideWeapon = equipment.getItem(row, col); }

    void addItemToInventory(int row, int col, const string& itemName) {
        equipment.addItem(row, col, itemName);
    }

    void displayGold() {
        cout << "Gold: " << gold << endl;
    }

    void addGold(int amount) {
        gold += amount;
    }

    int getGold() const {
        return gold;
    }

    void swapItemsInInventory(int row1, int col1, int row2, int col2) {
        equipment.swapItems(row1, col1, row2, col2);
    }

    void deleteItemFromInventory(int row, int col) {
        equipment.deleteItem(row, col);
    }

    void resizeInventory(int newRows, int newCols) {
        equipment.resizeEquipment(newRows, newCols);
    }
};

int main() {
    Player player;
    int choice, row, col, row2, col2, amount, newRows, newCols;
    string itemName;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display Equipment\n";
        cout << "2. Add Gold\n";
        cout << "3. Add Item to Inventory\n";
        cout << "4. Equip Armor\n";
        cout << "5. Equip Trousers\n";
        cout << "6. Equip Boots\n";
        cout << "7. Equip Main Weapon\n";
        cout << "8. Equip Side Weapon\n";
        cout << "9. Swap Items in Inventory\n";
        cout << "10. Delete Item from Inventory\n";
        cout << "11. Resize Inventory\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            player.displayEquipment();
            break;
        case 2:
            cout << "Enter amount of gold to add: ";
            cin >> amount;
            player.addGold(amount);
            player.displayGold();
            break;
        case 3:
            cout << "Enter row and column to add item: ";
            cin >> row >> col;
            cout << "Enter item name: ";
            cin >> itemName;
            player.addItemToInventory(row, col, itemName);
            break;
        case 4:
            cout << "Enter row and column to equip armor: ";
            cin >> row >> col;
            player.equipArmor(row, col);
            break;
        case 5:
            cout << "Enter row and column to equip trousers: ";
            cin >> row >> col;
            player.equipTrousers(row, col);
            break;
        case 6:
            cout << "Enter row and column to equip boots: ";
            cin >> row >> col;
            player.equipBoots(row, col);
            break;
        case 7:
            cout << "Enter row and column to equip main weapon: ";
            cin >> row >> col;
            player.equipMainWeapon(row, col);
            break;
        case 8:
            cout << "Enter row and column to equip side weapon: ";
            cin >> row >> col;
            player.equipSideWeapon(row, col);
            break;
        case 9:
            cout << "Enter row and column of first item: ";
            cin >> row >> col;
            cout << "Enter row and column of second item: ";
            cin >> row2 >> col2;
            player.swapItemsInInventory(row, col, row2, col2);
            break;
        case 10:
            cout << "Enter row and column to delete item: ";
            cin >> row >> col;
            player.deleteItemFromInventory(row, col);
            break;
        case 11:
            cout << "Enter new number of rows: ";
            cin >> newRows;
            cout << "Enter new number of columns: ";
            cin >> newCols;
            player.resizeInventory(newRows, newCols);
            break;
        case 12:
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
