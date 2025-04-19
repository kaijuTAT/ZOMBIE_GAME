// ---------- include/Item.hh ---------- // <<<--- UPDATED FILENAME
#ifndef ITEM_HH // <<<--- UPDATED GUARD
#define ITEM_HH // <<<--- UPDATED GUARD

#include <string>
#include <iostream> // For display method

// 代表游戏中的道具
struct Item {
    std::string name;
    std::string description;
    int attackBonus;
    int defenseBonus;
    int healthBonus;
    bool isConsumable;

    Item(std::string n, std::string desc, int atk, int def, int hp, bool consumable = false);
    Item(); // Default constructor

    void display() const;
};

#endif // ITEM_HH // <<<--- UPDATED GUARD