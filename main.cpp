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
        for(int j = 0; j < rows; j++) {
            delete[] grid[j];
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

        // Usuwanie starej tablicy
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

    void equipArmor(Item* item) { armor = item; }
    void equipTrousers(Item* item) { trousers = item; }
    void equipBoots(Item* item) { boots = item; }
    void equipMainWeapon(Item* item) { mainWeapon = item; }
    void equipSideWeapon(Item* item) { sideWeapon = item; }

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
};

int main()
{
    Player player;

    player.displayEquipment();

    // Przykład dodawania złota i wyświetlenia
    player.addGold(100);


    // Przykład dodawania przedmiotu do ekwipunku
    player.addItemToInventory(0, 0, "Helmet");
    player.displayEquipment();

    // Przykład wyposażenia postaci w przedmioty
    Item* helmet = new Item("Steel Helmet");
    Item* sword = new Item("Steel Sword");
    player.equipArmor(helmet);
    player.equipMainWeapon(sword);
    player.displayEquipment();

    return 0;
}
