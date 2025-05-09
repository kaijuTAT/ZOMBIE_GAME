// ---------- src/Item.cpp ----------
#include "../include/Item.hh" // <<<--- UPDATED INCLUDE
#include <iostream>

// Item 构造函数实现 THE 
Item::Item(std::string n, std::string desc, int atk, int def, int hp, bool consumable)
    : name(n), description(desc), attackBonus(atk), defenseBonus(def), healthBonus(hp), isConsumable(consumable) {}

Item::Item() : name("Unknown Item"), description("An undescribed item."), attackBonus(0), defenseBonus(0), healthBonus(0), isConsumable(false) {}

// Item display 实现  ITEM DISPLAY REALIZE
void Item::display() const {
    std::cout << name << " (" << description << ")";
    if (attackBonus != 0) std::cout << " [Atk+" << attackBonus << "]";
    if (defenseBonus != 0) std::cout << " [Def+" << defenseBonus << "]";
    if (healthBonus != 0) std::cout << " [HP+" << healthBonus << "]";
    if (isConsumable) std::cout << " [Consumable]";
}
