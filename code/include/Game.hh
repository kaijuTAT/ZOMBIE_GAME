// ---------- include/Game.hh ----------
#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <cstdlib>   // <<<--- ADDED for system() used via CLEAR_SCREEN
#include "Player.hh" // Include Player definition
#include "Action.hh" // Include Action definitions
#include "Room.hh"   // <<<--- ADDED FULL INCLUDE (replaces forward declaration)
#include "Zombie.hh" // <<<--- ADDED FULL INCLUDE (replaces forward declaration)

// <<<--- MOVED CLEAR_SCREEN Definition Here --- >>>
// Platform-specific clear screen command
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear" // Assumes Linux/macOS
#endif

// Game 类声明
class Game {
private:
    Player player;
    std::vector<std::unique_ptr<Room>> rooms;         // Owns rooms
    std::vector<std::unique_ptr<Zombie>> allZombies; // Owns all zombies
    Room* currentRoom;
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

public:
    // 构造函数
    Game();
    // 主运行函数
    void run();
    // Destructor (default is fine now with includes)
    ~Game() = default;
};

#endif // GAME_HH
