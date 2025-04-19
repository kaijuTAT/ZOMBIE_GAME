// ---------- include/Room.hh ---------- // <<<--- UPDATED FILENAME
#ifndef ROOM_HH // <<<--- UPDATED GUARD
#define ROOM_HH // <<<--- UPDATED GUARD

#include <string>
#include <vector>
#include <memory> // For unique_ptr
#include "Item.hh" // <<<--- UPDATED INCLUDE --- Needs full definition for unique_ptr<Item>

// 前向声明 Zombie 类，避免循环包含
class Zombie;

const int NUM_DIRECTIONS = 4; // N, S, E, W

// Room 类声明
class Room {
private:
    std::string description;
    Room* paths[NUM_DIRECTIONS];
    std::vector<std::unique_ptr<Item>> items; // Room owns items
    std::vector<Zombie*> zombies; // Room does NOT own zombies
    int roomNumber;

public:
    Room(std::string desc = "An empty room.", int number = 0);
    ~Room(); // Default destructor is fine due to unique_ptr

    std::string getDescription() const;
    int getRoomNumber() const;

    void setPath(int directionIndex, Room* room);
    Room* getPath(int directionIndex) const;
    static int directionIndex(const std::string& direction);
    static std::string directionName(int i);

    void addItem(std::unique_ptr<Item> item);
    std::unique_ptr<Item> removeItem(size_t index);
    const std::vector<std::unique_ptr<Item>>& getItems() const;

    void addZombie(Zombie* zombie);
    bool removeZombiePtr(Zombie* zombieToRemove); // Renamed for clarity
    const std::vector<Zombie*>& getZombies() const;
    std::vector<Zombie*>& getZombies(); // Non-const version

    void displayRoomInfo() const;
};

#endif // ROOM_HH // <<<--- UPDATED GUARD
