// ---------- include/Item.hh ----------
#ifndef ITEM_HH
#define ITEM_HH

#include <string>
#include <iostream>

/**
 * @file Item.hh
 * @brief Defines the Item struct, representing collectible items in the game.
 * Items have basic properties and effects on character stats.
 */

// 代表游戏中的道具
struct Item {
    std::string name;
    std::string description;
    int attackBonus;
    int defenseBonus;
    int healthBonus;
    bool isConsumable;

    // Constructors
    Item(std::string n, std::string desc, int atk, int def, int hp, bool consumable = false);
    Item();

    // Display method
    void display() const;

    // --- Canonical Form (Rule of Zero applies, defaulting is explicit) ---
    ~Item() = default; // Default destructor
    Item(const Item& other) = default; // Default copy constructor
    Item& operator=(const Item& other) = default; // Default copy assignment
    Item(Item&& other) noexcept = default; // Default move constructor
    Item& operator=(Item&& other) noexcept = default; // Default move assignment
};

#endif // ITEM_HH
