// ---------- include/Player.hh ---------- // <<<--- UPDATED FILENAME
#ifndef PLAYER_HH // <<<--- UPDATED GUARD
#define PLAYER_HH // <<<--- UPDATED GUARD

#include "ICharacter.hh" // <<<--- UPDATED INCLUDE --- 包含接口定义
#include <vector>
#include <string>
#include <memory>

// 前向声明 Item, ICharacter 已包含
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
    std::vector<std::unique_ptr<Item>> inventory;

public:
    Player(std::string n = "Survivor", std::string desc = "A lone survivor.", unsigned hp = 100, unsigned atk = 10, unsigned def = 5);
    virtual ~Player() override; // Use override keyword

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

#endif // PLAYER_HH // <<<--- UPDATED GUARD

