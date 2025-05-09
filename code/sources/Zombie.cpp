// ---------- src/Zombie.cpp ----------
#include "../include/Zombie.hh" // <<<--- UPDATED INCLUDE
#include <iostream>
#include <sstream>
#include <algorithm> // For std::max

Zombie::Zombie(std::string n, std::string desc, unsigned hp, unsigned atk, unsigned def)
    : name(n), description(desc), maxHealth(hp), health(hp), attackPower(atk), defensePower(def) {}

// Destructor defaulted in header

bool Zombie::isAlive() const { return health > 0; }

bool Zombie::takeDamage(unsigned damage) {
    int damageTaken = std::max(1, static_cast<int>(damage) - static_cast<int>(defensePower));
    std::cout << getName() << " takes " << damageTaken << " damage." << std::endl;
    if (static_cast<unsigned>(damageTaken) >= health) {
        health = 0;
        std::cout << getName() << " has been defeated!" << std::endl;
    } else {
        health -= static_cast<unsigned>(damageTaken);
    }
    return isAlive();
}

bool Zombie::attack(ICharacter& target) {
    std::cout << getName() << " lunges at " << target.getName() << "!" << std::endl;
    return target.takeDamage(attackPower);
}

std::string Zombie::getName() const { return name; }
std::string Zombie::getDescription() const { return description; }
unsigned Zombie::getHealth() const { return health; }
unsigned Zombie::getMaxHealth() const { return maxHealth; }
unsigned Zombie::getAttack() const { return attackPower; }
unsigned Zombie::getDefense() const { return defensePower; }

std::string Zombie::toString() const {
     std::stringstream ss;
    ss << name << " (HP: " << health << "/" << maxHealth << ")";
    return ss.str();
}

void Zombie::addToInventory(std::unique_ptr<Item> item) { /* No-op */ }
void Zombie::displayInventory() const { /* No-op */ }

void Zombie::display() const {
    std::cout << "--- Enemy Status ---" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "HP: " << health << "/" << maxHealth << std::endl;
    std::cout << "--------------------" << std::endl;
}

void Zombie::updateStatsFromInventory() { /* No-op */ }
void Zombie::useItem(size_t index) { /* No-op */ }
std::unique_ptr<Item> Zombie::dropItem(size_t index) { return nullptr; }

const std::vector<std::unique_ptr<Item>>& Zombie::getInventory() const {
    static const std::vector<std::unique_ptr<Item>> empty_inventory;
    return empty_inventory;
}

void Zombie::heal(unsigned amount) {
    // Zombies typically don't heal themselves in this way
    // No operation needed.
}