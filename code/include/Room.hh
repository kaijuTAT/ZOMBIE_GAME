// ---------- include/Room.hh ----------
#ifndef ROOM_HH
#define ROOM_HH

#include <string>
#include <vector>
#include <memory> // For unique_ptr
#include "Item.hh" // Needs full definition for unique_ptr<Item>

/**
 * @file Room.hh
 * @brief Defines the Room class, representing a location within the game world.
 * Rooms contain descriptions, exits, items, references to enemies, and potentially special effects.
 */

// 定义房间可能具有的特殊效果
enum class RoomEffect {
    NONE,         // 无特殊效果
    HEAL_SMALL,   // 进入时少量回血
    DAMAGE_SMALL  // 进入时受到少量伤害
    // 可以添加更多效果类型
};

// 前向声明 Zombie 类，避免循环包含
class Zombie;

const int NUM_DIRECTIONS = 4; // N, S, E, W

// Room 类声明
class Room {
private:
    std::string description;
    Room* paths[NUM_DIRECTIONS]; // Raw pointers, Room does not own adjacent rooms
    std::vector<std::unique_ptr<Item>> items; // Room owns items via unique_ptr
    std::vector<Zombie*> zombies; // Raw pointers, Room does NOT own zombies
    int roomNumber;
    RoomEffect effect; // 房间的特殊效果

public:
    // 构造函数 (接受效果作为参数)
    Room(std::string desc = "An empty room.", int number = 0, RoomEffect initialEffect = RoomEffect::NONE);

    // --- Canonical Form (Rule of Five/Zero) ---
    ~Room() = default;
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;
    Room(Room&&) noexcept = default;
    Room& operator=(Room&&) noexcept = default;

    // --- Public Methods ---
    std::string getDescription() const;
    int getRoomNumber() const;
    RoomEffect getEffect() const; // 获取房间效果

    void setPath(int directionIndex, Room* room);
    Room* getPath(int directionIndex) const;
    static int directionIndex(const std::string& direction);
    static std::string directionName(int i);

    void addItem(std::unique_ptr<Item> item);
    std::unique_ptr<Item> removeItem(size_t index);
    const std::vector<std::unique_ptr<Item>>& getItems() const;

    void addZombie(Zombie* zombie);
    bool removeZombiePtr(Zombie* zombieToRemove);
    const std::vector<Zombie*>& getZombies() const;
    std::vector<Zombie*>& getZombies(); // Non-const version

    void displayRoomInfo() const;
};

#endif // ROOM_HH
