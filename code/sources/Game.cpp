// ---------- src/Game.cpp ----------
#include "../include/Game.hh"   // Include Game header
#include "../include/Room.hh"   // Need full Room definition
#include "../include/Zombie.hh" // Need full Zombie definition
#include "../include/Item.hh"   // Need full Item definition
#include "../include/Action.hh" // Need Action definition
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <limits>    // For std::numeric_limits
#include <cstdlib>   // For system() and rand()/srand()
#include <algorithm> // For std::max/min
#include <cctype>    // For toupper
#include <random>    // For random number generation (alternative to rand)
#include <ctime>     // For seeding random number generator

// Game Constructor
Game::Game()
    : player("Hero", "Just trying to survive.", 100, 10, 2),
      currentRoom(nullptr), gameOver(false), playerWon(false) {
    setupGame(); // Call setup logic
}

// Destructor defaulted in header

// Game Setup Implementation
void Game::setupGame() {
    // Seed the random number generator once at the start
    srand(static_cast<unsigned int>(time(nullptr)));

    // --- 定义物品模板 ---
    // Store templates for potential random generation
    std::vector<Item> itemTemplates;
    itemTemplates.emplace_back("Medkit", "Restores some health.", 0, 0, 30, true);           // 0
    itemTemplates.emplace_back("Baseball Bat", "Good for bonking.", 5, 0, 0);                // 1
    itemTemplates.emplace_back("Energy Drink", "Temporary stamina boost.", 0, 0, 5, true);   // 2
    itemTemplates.emplace_back("Body Armor", "Provides some protection.", 0, 5, 0);         // 3
    itemTemplates.emplace_back("Canned Food", "Reduces hunger.", 0, 0, 10, true);            // 4
    itemTemplates.emplace_back("Rusty Pipe", "Better than nothing.", 3, 0, 0);               // 5
    itemTemplates.emplace_back("Painkillers", "Helps ignore the pain.", 0, 1, 5, true);      // 6
    itemTemplates.emplace_back("Bandage", "Stops minor bleeding.", 0, 0, 5, true);           // 7

    // --- 创建僵尸 ---
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Walker", "Slow but persistent.", 50, 8, 1)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Runner", "Disturbingly fast.", 35, 12, 0)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Bloater", "Tough and resilient.", 80, 10, 4)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Walker", "Another slow one.", 50, 8, 1)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Runner", "Quick and twitchy.", 35, 12, 0)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Crawler", "Low profile, surprisingly quick lunge.", 30, 7, 0)));

    // --- 创建房间 (指定效果) ---
    // [1] [2] [3]
    // [4] [5] [6]
    rooms.push_back(std::unique_ptr<Room>(new Room("You stand on a cracked asphalt street...", 1, RoomEffect::NONE))); // 0 START
    rooms.push_back(std::unique_ptr<Room>(new Room("Inside a ransacked convenience store...", 2, RoomEffect::DAMAGE_SMALL))); // 1 Damage Effect
    rooms.push_back(std::unique_ptr<Room>(new Room("A dark alleyway, smelling of decay...", 3, RoomEffect::NONE))); // 2
    rooms.push_back(std::unique_ptr<Room>(new Room("An abandoned office space...", 4, RoomEffect::HEAL_SMALL))); // 3 Heal Effect
    rooms.push_back(std::unique_ptr<Room>(new Room("The main lobby of a deserted building...", 5, RoomEffect::NONE))); // 4 END
    rooms.push_back(std::unique_ptr<Room>(new Room("A collapsed section of a parking garage...", 6, RoomEffect::NONE))); // 5

    // --- 连接房间 ---
    rooms[0]->setPath(2, rooms[1].get()); rooms[0]->setPath(1, rooms[3].get()); // Room 1 exits
    rooms[1]->setPath(3, rooms[0].get()); rooms[1]->setPath(1, rooms[4].get()); rooms[1]->setPath(2, rooms[2].get()); // Room 2 exits
    rooms[2]->setPath(1, rooms[5].get()); rooms[2]->setPath(3, rooms[1].get()); // Room 3 exits
    rooms[3]->setPath(0, rooms[0].get()); rooms[3]->setPath(2, rooms[4].get()); // Room 4 exits
    rooms[4]->setPath(0, rooms[1].get()); rooms[4]->setPath(3, rooms[3].get()); rooms[4]->setPath(2, rooms[5].get()); // Room 5 exits
    rooms[5]->setPath(0, rooms[2].get()); rooms[5]->setPath(3, rooms[4].get()); // Room 6 exits

    // --- 随机 + 固定放置物品 ---
    if (!itemTemplates.empty()) {
        // Place starting item
        rooms[0]->addItem(std::unique_ptr<Item>(new Item(itemTemplates[5]))); // Rusty Pipe in Start Room (1)

        // Random items in other non-end rooms
        for (size_t i = 1; i < rooms.size(); ++i) { // Start from index 1 (Room 2)
            if (rooms[i]->getRoomNumber() != 5) { // Skip the end room for random placement
                // 60% chance to spawn one item
                if ((rand() % 100) < 60) {
                    int itemIndex = rand() % itemTemplates.size(); // Random template index
                    // Ensure we don't duplicate unique items if needed (simple version allows duplicates)
                    rooms[i]->addItem(std::unique_ptr<Item>(new Item(itemTemplates[itemIndex])));
                    // std::cout << "DEBUG: Added random " << itemTemplates[itemIndex].name << " to Room " << rooms[i]->getRoomNumber() << std::endl;
                }
                 // Could add logic for a second item spawn chance here
            }
        }
        // Place guaranteed items in the end room
        rooms[4]->addItem(std::unique_ptr<Item>(new Item(itemTemplates[1]))); // Baseball Bat
        rooms[4]->addItem(std::unique_ptr<Item>(new Item(itemTemplates[3]))); // Body Armor
    }


    // --- 放置僵尸 ---
    rooms[1]->addZombie(allZombies[0].get()); // Room 2
    rooms[2]->addZombie(allZombies[5].get()); // Room 3
    rooms[3]->addZombie(allZombies[3].get()); // Room 4
    rooms[5]->addZombie(allZombies[1].get()); // Room 6
    rooms[5]->addZombie(allZombies[4].get()); // Room 6
    rooms[2]->addZombie(allZombies[2].get()); // Room 3 

    // --- 设置初始状态 ---
    currentRoom = rooms[0].get();
    player.updateStatsFromInventory();
}

// Game Display State Implementation
void Game::displayCurrentState() {
    system(CLEAR_SCREEN); // Uses macro defined in Game.hh
    if (!currentRoom) {
        std::cerr << "Error: currentRoom is null!" << std::endl;
        gameOver = true;
        return;
    }
    currentRoom->displayRoomInfo();
    std::cout << "\nPlayer: " << player.toString() << std::endl;

    currentActions.clear();
    int optionIndex = 1;
    std::cout << "\nWhat do you want to do?" << std::endl;

    // Movement options
    for (int i = 0; i < NUM_DIRECTIONS; ++i) {
        if (currentRoom->getPath(i) != nullptr) {
            std::cout << optionIndex << ". Move " << Room::directionName(i) << std::endl;
            currentActions[optionIndex] = ActionInfo(ActionType::MOVE, i);
            optionIndex++;
        }
    }
    // Pickup option
    if (!currentRoom->getItems().empty()) {
        std::cout << optionIndex << ". Pick up Item" << std::endl;
        currentActions[optionIndex] = ActionInfo(ActionType::PICKUP);
        optionIndex++;
    }
    // Attack option
    bool attackOptionAvailable = false;
    for(const auto* zombie : currentRoom->getZombies()) {
        if (zombie && zombie->isAlive()) {
            attackOptionAvailable = true;
            break;
        }
    }
    if (attackOptionAvailable) {
        std::cout << optionIndex << ". Attack Enemy" << std::endl;
        currentActions[optionIndex] = ActionInfo(ActionType::ATTACK);
        optionIndex++;
    }
    // Inventory option
    std::cout << optionIndex << ". Check Inventory" << std::endl;
    currentActions[optionIndex] = ActionInfo(ActionType::VIEW_INVENTORY);
    optionIndex++;
    // Status option
    std::cout << optionIndex << ". Check Status" << std::endl;
    currentActions[optionIndex] = ActionInfo(ActionType::VIEW_STATUS);
    optionIndex++;
}

// Game Get Player Action Choice Implementation
int Game::getPlayerActionChoice() {
    int maxChoice = currentActions.size();
    return getPlayerInput(1, maxChoice, "Enter your choice");
}

// Game Get Player List Choice Implementation
int Game::getPlayerListChoice(int listSize, const std::string& prompt) {
   return getPlayerInput(0, listSize, prompt);
}

// Game Get Player Input Implementation
int Game::getPlayerInput(int minChoice, int maxChoice, const std::string& prompt) {
    int choice = -1;
    std::cout << prompt << " (" << minChoice << "-" << maxChoice << "): ";
    while (!(std::cin >> choice) || choice < minChoice || choice > maxChoice) {
        std::cout << "Invalid input. Please enter a number between " << minChoice << " and " << maxChoice << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Requires <limits>
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Requires <limits>
    return choice;
}

// Game Process Player Action Implementation
void Game::processPlayerAction(int choice) {
    if (currentActions.find(choice) == currentActions.end()) {
        std::cout << "Invalid action selected." << std::endl;
        return;
    }
    ActionInfo action = currentActions[choice];

    switch (action.type) {
        case ActionType::MOVE: {
            Room* nextRoom = currentRoom->getPath(action.targetIndex);
            if (nextRoom) {
                currentRoom = nextRoom; // Update current room
                std::cout << "You move " << Room::directionName(action.targetIndex) << "." << std::endl;
                applyRoomEffect(currentRoom); // <<<--- Apply effect AFTER moving
                if (playerWon) return; // If effect caused win (unlikely but possible), stop
                if (!player.isAlive()) { // If effect caused death
                    gameOver = true;
                    return;
                }
                // Check win condition based on room number
                if (currentRoom->getRoomNumber() == 5) {
                    playerWon = true;
                }
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
            break;
        }
        case ActionType::PICKUP: {
            const auto& items = currentRoom->getItems();
            if (items.empty()) {
                std::cout << "There are no items to pick up." << std::endl;
            } else {
                int itemChoice = getPlayerListChoice(items.size(), "Pick up which item?");
                if (itemChoice > 0) {
                     std::unique_ptr<Item> pickedItem = currentRoom->removeItem(itemChoice);
                     if (pickedItem) {
                         player.addToInventory(std::move(pickedItem));
                     } else {
                         std::cout << "Failed to pick up item " << itemChoice << "." << std::endl;
                     }
                } else {
                    std::cout << "Cancelled pickup." << std::endl;
                }
            }
            break;
        }
        case ActionType::ATTACK: {
            std::vector<Zombie*> availableTargets;
            for (auto* zombie : currentRoom->getZombies()) {
                if (zombie && zombie->isAlive()) {
                    availableTargets.push_back(zombie);
                }
            }
            if (availableTargets.empty()) {
                std::cout << "There are no enemies to attack." << std::endl;
            } else {
                int targetChoice = getPlayerListChoice(availableTargets.size(), "Attack which enemy?");
                if (targetChoice > 0) {
                    Zombie* target = availableTargets[targetChoice - 1]; // Convert 1-based to 0-based index
                    if (target) {
                        player.attack(*target);
                    } else {
                        std::cout << "Invalid target selected." << std::endl; // Should not happen
                    }
                } else {
                    std::cout << "Cancelled attack." << std::endl;
                }
            }
            break;
        }
        case ActionType::VIEW_INVENTORY: {
            player.displayInventory();
            const auto& playerItems = player.getInventory();
            if (!playerItems.empty()) {
                int itemChoiceInput = getPlayerListChoice(playerItems.size(), "Enter item number to use (0 to cancel)");
                if (itemChoiceInput > 0) {
                    player.useItem(itemChoiceInput); // Pass 1-based index
                }
            }
            break;
        }
        case ActionType::VIEW_STATUS: {
            player.display();
            break;
        }
        default: {
            std::cout << "Unknown action." << std::endl;
            break;
        }
    }
}

// Game Handle Enemy Turn Implementation
void Game::handleEnemyTurn() {
    if (!currentRoom || !player.isAlive()) return; // Pre-checks

    std::cout << "\n--- Enemy Turn ---" << std::endl;
    bool enemyActed = false;
    std::vector<Zombie*> attackers; // List of zombies that can act this turn
    for (auto* zombie : currentRoom->getZombies()) {
        if (zombie && zombie->isAlive()) {
            attackers.push_back(zombie);
        }
    }

    for (auto* zombie : attackers) {
        if (!player.isAlive()) { // Check if player died mid-turn
            gameOver = true;
            break;
        }
        // Ensure zombie didn't die somehow before its action
        if (zombie && zombie->isAlive()){
             zombie->attack(player);
             enemyActed = true;
        }
    }

    if (!enemyActed && player.isAlive()) {
        std::cout << "No enemies acted." << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

// <<<--- Implementation for applyRoomEffect --- >>>
void Game::applyRoomEffect(Room* room) {
    if (!room || !player.isAlive()) { // Safety checks
        return;
    }

    switch (room->getEffect()) {
        case RoomEffect::HEAL_SMALL:
            std::cout << "You feel a soothing presence in this room." << std::endl;
            player.heal(10); // Call player's heal method
            break;
        case RoomEffect::DAMAGE_SMALL:
            std::cout << "A wave of nausea washes over you in this room!" << std::endl;
            player.takeDamage(5); // Apply damage to player
            // Check if player died from room effect
            if (!player.isAlive()) {
                gameOver = true;
            }
            break;
        case RoomEffect::NONE:
        default:
            // No effect
            break;
    }
}


// Game Run Implementation
void Game::run() {
    if (!currentRoom) {
         std::cerr << "Error: Game setup failed, no starting room!" << std::endl;
         return;
    }

    // Apply effect of the starting room immediately
    applyRoomEffect(currentRoom);
    if (!player.isAlive()) { gameOver = true; } // Check if died in starting room

    while (!gameOver && !playerWon) {
        displayCurrentState(); // Show room, player, menu
        if (gameOver) break;   // Check if display found an error

        int choice = getPlayerActionChoice(); // Get valid menu choice
        processPlayerAction(choice);          // Perform player action

        // Check game state immediately after player action
        if (playerWon) break;
        if (!player.isAlive()) { gameOver = true; break; }

        // If game continues, process enemy turn
        handleEnemyTurn();

        // Check game state again after enemy turn
        if (!player.isAlive()) { gameOver = true; }

        // Pause if game is still running
        if (!gameOver && !playerWon) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    } // End of game loop

    displayEndGameMessage(); // Show win/loss message

    // Final pause to see the message before window closes
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
}

// Game Display End Game Message Implementation
void Game::displayEndGameMessage() {
     system(CLEAR_SCREEN); // Uses macro defined in Game.hh
     if (playerWon) {
        std::cout << "\n*****************************************" << std::endl;
        std::cout << "*** VICTORY! You reached the safe lobby! ***" << std::endl;
        std::cout << "*****************************************" << std::endl;
     } else if (gameOver) {
        std::cout << "\n==================" << std::endl;
        std::cout << "=== GAME OVER ===" << std::endl;
        std::cout << "==================" << std::endl;
        std::cout << "\nYou did not survive..." << std::endl;
     } else {
        // This case should not normally be reached
        std::cout << "Game loop ended unexpectedly." << std::endl;
     }
}
