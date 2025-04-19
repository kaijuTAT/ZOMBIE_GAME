// ---------- src/Item.cpp ----------
// (如果 Item 方法在头文件中定义，则此文件为空或不存在)
#include "../include/Item.hh" // <<<--- UPDATED INCLUDE
#include <iostream>

// Item 构造函数实现 (如果在头文件中未内联)
Item::Item(std::string n, std::string desc, int atk, int def, int hp, bool consumable)
    : name(n), description(desc), attackBonus(atk), defenseBonus(def), healthBonus(hp), isConsumable(consumable) {}

Item::Item() : name("Unknown Item"), description("An undescribed item."), attackBonus(0), defenseBonus(0), healthBonus(0), isConsumable(false) {}

// Item display 实现 (如果在头文件中未内联)
void Item::display() const {
    std::cout << name << " (" << description << ")";
    if (attackBonus != 0) std::cout << " [Atk+" << attackBonus << "]";
    if (defenseBonus != 0) std::cout << " [Def+" << defenseBonus << "]";
    if (healthBonus != 0) std::cout << " [HP+" << healthBonus << "]";
    if (isConsumable) std::cout << " [Consumable]";
}