// ---------- src/Room.cpp ----------
#include "../include/Room.hh"   // <<<--- UPDATED INCLUDE
#include "../include/Zombie.hh" // <<<--- UPDATED INCLUDE
#include "../include/Item.hh"   // <<<--- UPDATED INCLUDE
#include <iostream>
#include <cctype> // For toupper

Room::Room(std::string desc, int number)
    : description(desc), roomNumber(number) {
    for (int i = 0; i < NUM_DIRECTIONS; ++i) { paths[i] = nullptr; }
}

Room::~Room() = default;

std::string Room::getDescription() const { return description; }
int Room::getRoomNumber() const { return roomNumber; }

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

// Static methods defined in header are implicitly inline or need separate definition
// Let's assume they are simple enough for header or defined here if complex
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

void Room::displayRoomInfo() const {
    std::cout << "\n=== Room " << roomNumber << " ===" << std::endl;
    std::cout << description << std::endl;

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