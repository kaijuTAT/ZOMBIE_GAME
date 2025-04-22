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
#include <limits>    // <<<--- ADDED INCLUDE for std::numeric_limits (used in getPlayerInput)
#include <cstdlib>   // For system() - already included via Game.hh now, but good practice
#include <algorithm>
#include <cctype>

// ... (Rest of Game.cpp implementation remains the same) ...

// Game Constructor
Game::Game()
    : player("Hero", "Just trying to survive.", 100, 10, 2),
      currentRoom(nullptr), gameOver(false), playerWon(false) {
    setupGame(); // Call setup logic
}

// Game Setup Implementation
void Game::setupGame() {
    // --- Create Items ---
    auto item1 = std::unique_ptr<Item>(new Item("Medkit", "Restores some health.", 0, 0, 30, true));
    auto item2 = std::unique_ptr<Item>(new Item("Baseball Bat", "Good for bonking.", 5, 0, 0));
    auto item3 = std::unique_ptr<Item>(new Item("Energy Drink", "Temporary stamina boost (effect not implemented).", 0, 0, 5, true));
    auto item4 = std::unique_ptr<Item>(new Item("Body Armor", "Provides some protection.", 0, 5, 0));
    auto item5 = std::unique_ptr<Item>(new Item("Canned Food", "Reduces hunger (effect not implemented).", 0, 0, 10, true));
    auto item6 = std::unique_ptr<Item>(new Item("Rusty Pipe", "Better than nothing.", 3, 0, 0));
    auto item7 = std::unique_ptr<Item>(new Item("Painkillers", "Helps ignore the pain (temp def boost?).", 0, 1, 5, true));

    // --- Create Zombies ---
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Walker", "Slow but persistent.", 50, 8, 1)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Runner", "Disturbingly fast.", 35, 12, 0)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Bloater", "Tough and resilient.", 80, 10, 4)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Walker", "Another slow one.", 50, 8, 1)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Runner", "Quick and twitchy.", 35, 12, 0)));
    allZombies.push_back(std::unique_ptr<Zombie>(new Zombie("Crawler", "Low profile, surprisingly quick lunge.", 30, 7, 0)));

    // --- Create Rooms (6 rooms) ---
    rooms.push_back(std::unique_ptr<Room>(new Room("You stand on a cracked asphalt street. An eerie silence hangs in the air.", 1))); // 0
    rooms.push_back(std::unique_ptr<Room>(new Room("Inside a ransacked convenience store. Empty shelves and broken glass.", 2))); // 1
    rooms.push_back(std::unique_ptr<Room>(new Room("A dark alleyway, smelling of decay. A dead end.", 3)));                     // 2
    rooms.push_back(std::unique_ptr<Room>(new Room("An abandoned office space. Papers litter the floor.", 4)));                 // 3
    rooms.push_back(std::unique_ptr<Room>(new Room("The main lobby of a deserted building. Seems secure for now.", 5)));       // 4 END
    rooms.push_back(std::unique_ptr<Room>(new Room("A collapsed section of a parking garage. Watch your step.", 6)));          // 5

    // --- Link Rooms (Indices: N=0, S=1, E=2, W=3) ---
    rooms[0]->setPath(2, rooms[1].get()); // 1 E -> 2
    rooms[0]->setPath(1, rooms[3].get()); // 1 S -> 4 
    rooms[1]->setPath(3, rooms[0].get()); // 2 W -> 1
    rooms[1]->setPath(1, rooms[4].get()); // 2 S -> 5 (End)
    rooms[1]->setPath(2, rooms[2].get()); // 2 E -> 3
    rooms[2]->setPath(1, rooms[5].get()); // 3 S -> 6
    rooms[2]->setPath(3, rooms[1].get()); // 3 W -> 2
    rooms[3]->setPath(2, rooms[4].get()); // 4 E -> 5 (End)
    rooms[3]->setPath(0, rooms[0].get()); // 4 N -> 1 
    rooms[4]->setPath(0, rooms[1].get()); // 5 N -> 2
    rooms[4]->setPath(3, rooms[3].get()); // 5 W -> 4
    rooms[4]->setPath(2, rooms[5].get()); // 5 E -> 6
    rooms[5]->setPath(0, rooms[2].get()); // 6 N -> 3
    rooms[5]->setPath(3, rooms[4].get()); // 6 W -> 5 (End)

    // --- Place Items ---
    rooms[0]->addItem(std::move(item6)); // Room 1
    rooms[1]->addItem(std::move(item3)); // Room 2
    rooms[2]->addItem(std::move(item5)); // Room 3
    rooms[3]->addItem(std::move(item1)); // Room 4
    rooms[5]->addItem(std::move(item7)); // Room 6
    rooms[4]->addItem(std::move(item2)); // Room 5 (End)
    rooms[4]->addItem(std::move(item4)); // Room 5 (End)

    // --- Place Zombies ---
    rooms[1]->addZombie(allZombies[0].get()); // Room 2
    rooms[2]->addZombie(allZombies[5].get()); // Room 3
    rooms[3]->addZombie(allZombies[3].get()); // Room 4
    rooms[5]->addZombie(allZombies[1].get()); // Room 6
    rooms[5]->addZombie(allZombies[4].get()); // Room 6
    rooms[2]->addZombie(allZombies[2].get()); // Room 5 (End)

    // --- Set initial state ---
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
        // <<<--- Requires <limits> --- >>>
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
     // <<<--- Requires <limits> --- >>>
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                currentRoom = nextRoom;
                std::cout << "You move " << Room::directionName(action.targetIndex) << "." << std::endl;
                if (currentRoom->getRoomNumber() == 5) { // Check win condition (Room 5)
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

// Game Run Implementation
void Game::run() {
    if (!currentRoom) {
         std::cerr << "Error: Game setup failed, no starting room!" << std::endl;
         return;
    }

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

// ... (Rest of implementation files: Player.cpp, Zombie.cpp, Room.cpp) ...
// ... (These remain the same as the previous version, just ensure their #includes use .hh) ...
