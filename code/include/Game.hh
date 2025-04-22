// ---------- include/Game.hh ----------
#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <cstdlib>   // For system() used via CLEAR_SCREEN
#include "Player.hh" // Include Player definition
#include "Action.hh" // Include Action definitions
#include "Room.hh"   // Include Room definition
#include "Zombie.hh" // Include Zombie definition

/**
 * @file Game.hh
 * @brief Defines the main Game class, responsible for managing the game state,
 * game loop, player interactions, and overall flow.
 */

// Platform-specific clear screen command
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear" // Assumes Linux/macOS
#endif

// Game 类声明
class Game {
private:
    Player player; // Game owns the player object
    std::vector<std::unique_ptr<Room>> rooms;         // Game owns rooms via unique_ptr
    std::vector<std::unique_ptr<Zombie>> allZombies; // Game owns all zombies via unique_ptr
    Room* currentRoom; // Pointer to the current room (doesn't own)
    bool gameOver;
    bool playerWon;
    std::map<int, ActionInfo> currentActions; // Menu number -> Action

    // --- 私有辅助方法声明 ---
    void setupGame();
    void displayCurrentState();
    int getPlayerActionChoice();
    int getPlayerListChoice(int listSize, const std::string& prompt);
    int getPlayerInput(int minChoice, int maxChoice, const std::string& prompt);
    void processPlayerAction(int choice);
    void handleEnemyTurn();
    void displayEndGameMessage();
    void applyRoomEffect(Room* room);

public:
    // Constructor
    Game();

    // --- Canonical Form (Rule of Five/Zero) ---
    // Destructor is defaulted (unique_ptrs handle cleanup)
    ~Game() = default;
    // Delete copy operations (managing unique_ptrs and complex state)
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    // Default move operations (all members are movable or trivially movable)
    Game(Game&&) noexcept = default;
    Game& operator=(Game&&) noexcept = default;

    // 主运行函数
    void run();
};

#endif // GAME_HH
