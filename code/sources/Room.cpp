// ---------- src/Room.cpp ----------
#include "../include/Room.hh"   // Include Room header
#include "../include/Zombie.hh" // Include Zombie definition for display
#include "../include/Item.hh"   // Include Item definition for display
#include <iostream>
#include <cctype> // For toupper

// 构造函数实现 
Room::Room(std::string desc, int number, RoomEffect initialEffect)
    : description(desc), roomNumber(number), effect(initialEffect) {
    for (int i = 0; i < NUM_DIRECTIONS; ++i) { paths[i] = nullptr; }
}

// Destructor defaulted in header

std::string Room::getDescription() const { return description; }
int Room::getRoomNumber() const { return roomNumber; }

// 获取房间效果实现 GET THE 
RoomEffect Room::getEffect() const {
    return effect;
}

void Room::setPath(int directionIndex, Room* room) {
    if (directionIndex >= 0 && directionIndex < NUM_DIRECTIONS) {
        paths[directionIndex] = room;
    }
}

Room* Room::getPath(int directionIndex) const {
    if (directionIndex >= 0 && directionIndex < NUM_DIRECTIONS) {
        return paths[directionIndex];
    }
    return nullptr;
}

// Static methods
int Room::directionIndex(const std::string& direction) {
    std::string upperDir = direction;
    for (char &c : upperDir) { c = toupper(c); }
    if (upperDir == "NORTH") return 0;
    if (upperDir == "SOUTH") return 1;
    if (upperDir == "EAST") return 2;
    if (upperDir == "WEST") return 3;
    return -1;
}

std::string Room::directionName(int i) {
    if (i == 0) return "North";
    if (i == 1) return "South";
    if (i == 2) return "East";
    if (i == 3) return "West";
    return "Unknown";
}
// End Static methods

void Room::addItem(std::unique_ptr<Item> item) {
    if (item) { items.push_back(std::move(item)); }
}

std::unique_ptr<Item> Room::removeItem(size_t index) {
    size_t actualIndex = index - 1;
    if (actualIndex < items.size()) {
        std::unique_ptr<Item> removedItem = std::move(items[actualIndex]);
        items.erase(items.begin() + actualIndex);
        return removedItem;
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Item>>& Room::getItems() const { return items; }

void Room::addZombie(Zombie* zombie) {
    if (zombie) { zombies.push_back(zombie); }
}

bool Room::removeZombiePtr(Zombie* zombieToRemove) {
    for (auto it = zombies.begin(); it != zombies.end(); ++it) {
        if (*it == zombieToRemove) {
            zombies.erase(it);
            return true;
        }
    }
    return false;
}

const std::vector<Zombie*>& Room::getZombies() const { return zombies; }
std::vector<Zombie*>& Room::getZombies() { return zombies; }

// 显示房间信息，包含效果提示 SHOWING THE IFORMATION OF THE ROOM, INCLUDE THE EFFECT
void Room::displayRoomInfo() const {
    std::cout << "\n=== Room " << roomNumber << " ===" << std::endl;
    std::cout << description << std::endl;

    // REPESENT THE EFFECT OF THE ROOM
    switch(effect) {
        case RoomEffect::HEAL_SMALL:
            std::cout << "(You feel a faint sense of recovery here.)" << std::endl;
            break;
        case RoomEffect::DAMAGE_SMALL:
            std::cout << "(The air here feels heavy and harmful.)" << std::endl;
            break;
        default: // RoomEffect::NONE or others
            break;
    }

    // 显示物品 DISPLAY THE ITEM
    std::cout << "\nItems:" << std::endl;
    if (items.empty()) {
        std::cout << "  None" << std::endl;
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "  " << i + 1 << ". ";
            if (items[i]) { items[i]->display(); }
            std::cout << std::endl;
        }
    }

    // 显示敌人 DISPLAY THE ENIMY
    std::cout << "\nEnemies:" << std::endl;
    bool enemyFound = false;
    int enemyCount = 1;
    for (const auto* zombie : zombies) {
        if (zombie && zombie->isAlive()) {
            std::cout << "  " << enemyCount++ << ". " << zombie->toString() << std::endl;
            enemyFound = true;
        }
    }
    if (!enemyFound) {
        std::cout << "  None" << std::endl;
    }

    // 显示出口 DISPLAY THE EXIT
    std::cout << "\nExits: ";
    bool exitFound = false;
    for (int i = 0; i < NUM_DIRECTIONS; ++i) {
        if (paths[i] != nullptr) {
            std::cout << directionName(i) << " ";
            exitFound = true;
        }
    }
    if (!exitFound) {
        std::cout << "None";
    }
    std::cout << std::endl;
}
