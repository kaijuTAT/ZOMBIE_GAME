// ---------- include/ICharacter.hh ----------
#ifndef ICHARACTER_HH
#define ICHARACTER_HH

#include <string>
#include <vector>
#include <memory> // For unique_ptr

#include "Item.hh" // Needs Item definition for unique_ptr<Item>

/**
 * @file ICharacter.hh
 * @brief Defines the ICharacter interface, specifying the common contract
 * for all characters (Player and Zombie) in the game.
 */

// 角色行为的统一接口规范
class ICharacter {
public:
    // Virtual destructor is essential for polymorphic base classes
    virtual ~ICharacter() = default;

    // --- Pure Virtual Functions (Must be implemented by derived classes) ---
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
    virtual void heal(unsigned amount) = 0; 
    // --- Canonical Form (Interface specific) ---
    // Interfaces typically don't need copy/move operations defined,
    // but deleting them prevents slicing if someone tries to copy via the interface.
    ICharacter(const ICharacter&) = delete;
    ICharacter& operator=(const ICharacter&) = delete;
    ICharacter(ICharacter&&) = delete;
    ICharacter& operator=(ICharacter&&) = delete;

protected:
    // Protected default constructor to allow derived class construction
    ICharacter() = default;
};

#endif // ICHARACTER_HH