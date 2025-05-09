// ---------- include/Player.hh ----------
#ifndef PLAYER_HH
#define PLAYER_HH

#include "ICharacter.hh" // 包含接口定义
#include <vector>
#include <string>
#include <memory> // For unique_ptr

/**
 * @file Player.hh
 * @brief Defines the Player class, representing the user-controlled character.
 * Manages player stats, inventory, and actions, implementing ICharacter.
 */

// Forward declare Item struct if needed, but ICharacter includes it
// struct Item;

// Player 类声明
class Player : public ICharacter {
private:
    std::string name;
    std::string description;
    unsigned health;
    unsigned maxHealth;
    unsigned currentMaxHealth;
    unsigned baseAttack;
    unsigned baseDefense;
    unsigned currentAttack;
    unsigned currentDefense;
    std::vector<std::unique_ptr<Item>> inventory; // Manages non-copyable resources

public:
    // Constructor
    Player(std::string n = "Survivor", std::string desc = "A lone survivor.", unsigned hp = 100, unsigned atk = 10, unsigned def = 5);

    // --- Canonical Form (Rule of Five/Zero) ---
    // Destructor is defaulted (unique_ptr handles cleanup)
    virtual ~Player() override = default;
    // Delete copy operations because inventory contains unique_ptr (non-copyable)
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    // Default move operations (unique_ptr is movable)
    Player(Player&&) noexcept = default;
    Player& operator=(Player&&) noexcept = default;


    // --- ICharacter 接口实现声明 ---
    bool isAlive() const override;
    bool takeDamage(unsigned damage) override;
    bool attack(ICharacter& target) override;
    std::string getName() const override;
    std::string getDescription() const override;
    unsigned getHealth() const override;
    unsigned getMaxHealth() const override;
    unsigned getAttack() const override;
    unsigned getDefense() const override;
    std::string toString() const override;
    void addToInventory(std::unique_ptr<Item> item) override;
    void displayInventory() const override;
    void display() const override;
    void updateStatsFromInventory() override;
    void useItem(size_t index) override;
    std::unique_ptr<Item> dropItem(size_t index) override;
    const std::vector<std::unique_ptr<Item>>& getInventory() const override;
    void heal(unsigned amount) override; 
};

#endif // PLAYER_HH

