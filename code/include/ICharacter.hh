// ---------- include/ICharacter.hh ---------- // <<<--- UPDATED FILENAME
#ifndef ICHARACTER_HH // <<<--- UPDATED GUARD
#define ICHARACTER_HH // <<<--- UPDATED GUARD

#include <string>
#include <vector>
#include <memory> // For unique_ptr

// 前向声明 Item 结构体，避免在头文件中包含 Item.hh 的全部内容 (如果 Item 定义很大)
// 但因为 Item 很小且在此处被广泛使用 (unique_ptr<Item>), 直接包含更方便
#include "Item.hh" // <<<--- UPDATED INCLUDE --- Item is used directly in method signatures

// 角色行为的统一接口规范
class ICharacter {
public:
    virtual ~ICharacter() = default;
    virtual bool isAlive() const = 0;
    virtual bool takeDamage(unsigned damage) = 0;
    virtual bool attack(ICharacter& target) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual unsigned getHealth() const = 0;
    virtual unsigned getAttack() const = 0;
    virtual unsigned getDefense() const = 0;
    virtual std::string toString() const = 0;
    virtual void addToInventory(std::unique_ptr<Item> item) = 0;
    virtual void displayInventory() const = 0;
    virtual void display() const = 0;
    virtual unsigned getMaxHealth() const = 0;
    virtual void updateStatsFromInventory() = 0;
    virtual void useItem(size_t index) = 0;
    virtual std::unique_ptr<Item> dropItem(size_t index) = 0;
    virtual const std::vector<std::unique_ptr<Item>>& getInventory() const = 0;
};

#endif // ICHARACTER_HH // <<<--- UPDATED GUARD