// ---------- include/Zombie.hh ---------- // <<<--- UPDATED FILENAME
#ifndef ZOMBIE_HH // <<<--- UPDATED GUARD
#define ZOMBIE_HH // <<<--- UPDATED GUARD

#include "ICharacter.hh" // <<<--- UPDATED INCLUDE --- 包含接口定义
#include <vector>       // For static empty vector in getInventory
#include <string>
#include <memory>

// 前向声明 Item, ICharacter 已包含
// struct Item;

// Zombie 类声明
class Zombie : public ICharacter {
private:
    std::string name;
    std::string description;
    unsigned health;
    unsigned maxHealth;
    unsigned attackPower;
    unsigned defensePower;

public:
    Zombie(std::string n = "Walker", std::string desc = "A shambling corpse.", unsigned hp = 50, unsigned atk = 8, unsigned def = 2);
    virtual ~Zombie() override; // Use override keyword

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
};

#endif // ZOMBIE_HH // <<<--- UPDATED GUARD
