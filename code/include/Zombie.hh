// ---------- include/Zombie.hh ----------
#ifndef ZOMBIE_HH
#define ZOMBIE_HH

#include "ICharacter.hh" // 包含接口定义 INCLUDE THE DECLARATION OF THE INTERFACES
#include <vector>
#include <string>
#include <memory> // For unique_ptr in getInventory return

/**
 * @file Zombie.hh
 * @brief Defines the Zombie class, representing enemy characters.
 * Implements the ICharacter interface with zombie-specific behavior.
 */

// Forward declare Item struct if needed, but ICharacter includes it
// struct Item;

// Zombie 类声明 ZOMBIE CLASS DECLARATION
class Zombie : public ICharacter {
private:
    std::string name;
    std::string description;
    unsigned health;
    unsigned maxHealth;
    unsigned attackPower;
    unsigned defensePower;

public:
    // Constructor
    Zombie(std::string n = "Walker", std::string desc = "A shambling corpse.", unsigned hp = 50, unsigned atk = 8, unsigned def = 2);

    // --- Canonical Form (Rule of Zero applies, defaulting is explicit) ---
    virtual ~Zombie() override = default; // Default destructor
    Zombie(const Zombie& other) = default; // Default copy constructor
    Zombie& operator=(const Zombie& other) = default; // Default copy assignment
    Zombie(Zombie&& other) noexcept = default; // Default move constructor
    Zombie& operator=(Zombie&& other) noexcept = default; // Default move assignment

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

#endif // ZOMBIE_HH