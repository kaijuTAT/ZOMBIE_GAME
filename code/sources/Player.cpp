// ---------- src/Player.cpp ----------
#include "../include/Player.hh" // <<<--- UPDATED INCLUDE
#include "../include/Item.hh"   // <<<--- UPDATED INCLUDE
#include <iostream>
#include <sstream>
#include <algorithm> // For std::max, std::min

Player::Player(std::string n, std::string desc, unsigned hp, unsigned atk, unsigned def)
    : name(n), description(desc), maxHealth(hp), currentMaxHealth(hp), health(hp),
      baseAttack(atk), baseDefense(def), currentAttack(atk), currentDefense(def) {
    inventory.reserve(10);
}

// Destructor defaulted in header

bool Player::isAlive() const { return health > 0; }

bool Player::takeDamage(unsigned damage) {
    int damageTaken = std::max(1, static_cast<int>(damage) - static_cast<int>(currentDefense));
    std::cout << getName() << " takes " << damageTaken << " damage." << std::endl;
    if (static_cast<unsigned>(damageTaken) >= health) {
        health = 0;
    } else {
        health -= static_cast<unsigned>(damageTaken);
    }
    return isAlive();
}

bool Player::attack(ICharacter& target) {
    std::cout << getName() << " attacks " << target.getName() << "!" << std::endl;
    return target.takeDamage(currentAttack);
}

std::string Player::getName() const { return name; }
std::string Player::getDescription() const { return description; }
unsigned Player::getHealth() const { return health; }
unsigned Player::getMaxHealth() const { return currentMaxHealth; }
unsigned Player::getAttack() const { return currentAttack; }
unsigned Player::getDefense() const { return currentDefense; }

std::string Player::toString() const {
    std::stringstream ss;
    ss << name << " (HP: " << health << "/" << currentMaxHealth << ", Atk: " << currentAttack << ", Def: " << currentDefense << ")";
    return ss.str();
}

void Player::addToInventory(std::unique_ptr<Item> item) {
    if (item) {
        std::cout << item->name << " added to inventory." << std::endl;
        inventory.push_back(std::move(item));
        updateStatsFromInventory();
    }
}

void Player::displayInventory() const {
    std::cout << "\n--- Inventory ---" << std::endl;
    if (inventory.empty()) {
        std::cout << "Inventory is empty." << std::endl;
    } else {
        for (size_t i = 0; i < inventory.size(); ++i) {
            std::cout << i + 1 << ". ";
            if (inventory[i]) {
                inventory[i]->display();
            } else {
                std::cout << "[Empty Slot - Error]";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "-----------------" << std::endl;
}

void Player::display() const {
    std::cout << "--- Player Status ---" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "HP: " << health << "/" << currentMaxHealth << std::endl;
    std::cout << "Base Attack: " << baseAttack << std::endl;
    std::cout << "Base Defense: " << baseDefense << std::endl;
    std::cout << "Current Attack: " << currentAttack << std::endl;
    std::cout << "Current Defense: " << currentDefense << std::endl;
    std::cout << "---------------------" << std::endl;
}

void Player::updateStatsFromInventory() {
    currentAttack = baseAttack;
    currentDefense = baseDefense;
    for (const auto& itemPtr : inventory) {
        if (itemPtr && !itemPtr->isConsumable) {
            currentAttack += itemPtr->attackBonus;
            currentDefense += itemPtr->defenseBonus;
        }
    }
    health = std::min(health, currentMaxHealth);
}

void Player::useItem(size_t index) {
    size_t actualIndex = index - 1;
    if (actualIndex < inventory.size() && inventory[actualIndex] != nullptr) {
        Item* itemToUse = inventory[actualIndex].get();
        if (itemToUse->isConsumable) {
            std::cout << "Using " << itemToUse->name << "." << std::endl;
            if (itemToUse->healthBonus > 0) {
                unsigned healAmount = static_cast<unsigned>(itemToUse->healthBonus);
                health = std::min(health + healAmount, currentMaxHealth);
                std::cout << "Healed for " << healAmount << " HP. Current HP: " << health << "/" << currentMaxHealth << std::endl;
            }
            inventory.erase(inventory.begin() + actualIndex);
            updateStatsFromInventory();
        } else {
            std::cout << itemToUse->name << " cannot be used like that (it's not consumable)." << std::endl;
        }
    } else {
        std::cout << "Invalid item number." << std::endl;
    }
}

std::unique_ptr<Item> Player::dropItem(size_t index) {
    size_t actualIndex = index - 1;
    if (actualIndex < inventory.size() && inventory[actualIndex] != nullptr) {
        std::unique_ptr<Item> itemToDrop = std::move(inventory[actualIndex]);
        inventory.erase(inventory.begin() + actualIndex);
        std::cout << itemToDrop->name << " dropped." << std::endl;
        updateStatsFromInventory();
        return itemToDrop;
    }
    std::cout << "Invalid item number." << std::endl;
    return nullptr;
}

const std::vector<std::unique_ptr<Item>>& Player::getInventory() const {
    return inventory;
}


void Player::heal(unsigned amount) {
    if (amount == 0 || !isAlive()) { // 不能治疗 0 点或死亡状态
        return;
    }
    unsigned oldHealth = health;
    health = std::min(health + amount, currentMaxHealth); // 治疗，不超过最大生命值
    unsigned healedAmount = health - oldHealth; // 计算实际治疗量
    if (healedAmount > 0) {
        std::cout << getName() << " recovers " << healedAmount << " HP." << std::endl;
    }
}