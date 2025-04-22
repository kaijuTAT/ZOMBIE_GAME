# Zomboid: Final Shelter - C++ Text-Based RPG

## 1. Project Overview

**Zomboid: Final Shelter** is a text-based Role-Playing Game (RPG) developed in C++. This project simulates a survival challenge within a post-apocalyptic zombie environment. Players assume the role of a survivor navigating through desolate urban settings, scavenging resources, combating zombies, and ultimately striving to reach a designated safe point. The game utilizes a command-line interface with interaction driven by a numerical menu system. It serves as a learning project to practice core C++ concepts such as object-oriented programming, memory management, and multi-file project organization.

## 2. Project Background and Objectives

* **Theme:** Zombie Apocalypse, Survival Horror
* **Core Gameplay:** Explore interconnected rooms, manage vital stats (health/stamina), engage in text-based combat, and collect items to enhance survivability.
* **Project Goals:**
    * Implement a fully functional text adventure game loop.
    * Apply core C++ features, including classes, inheritance, virtual functions (interfaces), pointers, and smart pointers (`std::unique_ptr`).
    * Construct a clear multi-file project structure (`.hh` / `.cpp`).
    * Practice object-oriented design principles.
    * Master the basic command-line compilation process (g++).

## 3. Core Features

* **Text-Driven Interaction:** Game progression is entirely driven by console text descriptions and player menu selections.
* **Diverse Game Elements:**
    * **Environmental Exploration:** Features 6 interconnected rooms (3x2 layout) with distinct descriptions and contents.
    * **Enemy Variety:** Includes at least 4 types of zombies with differing stats and behaviors (Walker, Runner, Bloater, Crawler).
    * **Item System:** Contains 7 collectible items providing attribute bonuses (weapons, armor) or restorative effects (consumables).
* **Survival Mechanics:** Players must manage health and utilize items to modify attack and defense attributes.
* **Object-Oriented Architecture:**
    * Utilizes the `ICharacter` interface to standardize character behavior.
    * `Player` and `Zombie` classes inherit from `ICharacter`.
    * `Room` class encapsulates location information and logic.
    * `Game` class manages the overall game flow and state.
* **C++ Feature Application:**
    * **Pointers:** Used for room connections (`Room* paths[]`) and referencing globally managed zombie objects within rooms (`Zombie*`).
    * **Smart Pointers:** Employs `std::unique_ptr` for automatic memory management of dynamically allocated resources (like `Item`, `Zombie`, `Room` objects), ensuring memory safety and preventing leaks.
    * **Inheritance & Polymorphism:** Achieved through the `ICharacter` interface and virtual functions for unified handling of player and zombies.
    * **STL Containers:** Uses `std::vector` for player inventory, room items, and zombie lists; `std::map` for mapping menu options to actions.
    * **Enum Class:** Defines clear action types using `enum class ActionType`.
* **Modular Code:** Source code is separated into header (`.hh`) and implementation (`.cpp`) files, organized into `include/` and `src/` directories.
* **Clear Win Condition:** Reaching the designated Room #5 (Abandoned Building Lobby).
* **User-Friendly Menu:** Number-based menu system guides player actions.
* **Basic Cross-Platform Compatibility:** Uses standard C++ and basic console operations, allowing potential compilation and execution on different systems.

## 4. Technology Stack

* **Language:** C++ (Requires C++11 standard or higher)
* **Core Libraries:** Standard Template Library (STL), `<iostream>`, `<string>`, `<vector>`, `<memory>`, `<map>`, `<sstream>`, `<limits>`, `<algorithm>`, `<cctype>`, `<cstdlib>`
* **Compilation:** g++ (Recommended) or other C++11-compatible compilers (e.g., Clang, MSVC)

## 5. Installation and Execution

### 5.1. Prerequisites

* A C++ compiler supporting C++11 or later (e.g., g++ >= 4.8).
* (Optional) Git client for cloning the repository.

### 5.2. Compilation Steps (Using g++)

1.  **Clone the Repository:**
    ```bash
    git clone <your-repository-url>
    cd YourProjectFolder
    ```
    Alternatively, download the ZIP file and extract it.

2.  **Verify Directory Structure:**
    ```
    YourProjectFolder/
    ├── include/     (*.hh files)
    └── src/         (*.cpp files)
    ```

3.  **Navigate to Source Directory:**
    ```bash
    cd src
    ```

4.  **Compile the Code:**
    ```bash
    g++ main.cpp Player.cpp Zombie.cpp Room.cpp Game.cpp Item.cpp Action.cpp -o zomboid_game -std=c++11 -I../include -Wall -Wextra -pedantic
    ```
    * **Explanation:**
        * `main.cpp ... Action.cpp`: List all `.cpp` files to be compiled. Omit `Item.cpp` or `Action.cpp` if they are empty (implementations in headers).
        * `-o zomboid_game`: Specifies the output executable name as `zomboid_game`.
        * `-std=c++11`: Enforces the C++11 standard.
        * `-I../include`: Specifies the include path for header files.
        * `-Wall -Wextra -pedantic`: (Recommended) Enables additional compiler warnings for better code quality.

### 5.3. Running the Game

* **Linux / macOS:**
    ```bash
    ./zomboid_game
    ```
* **Windows (MinGW/MSYS2/Cygwin):**
    ```bash
    ./zomboid_game.exe
    ```
* **Windows (CMD/PowerShell):**
    ```powershell
    .\zomboid_game.exe
    ```

## 6. Code Structure Details

* **`include/` Directory:**
    * `ICharacter.hh`: Defines the character interface class.
    * `Item.hh`: Defines the `Item` struct.
    * `Action.hh`: Defines the `ActionType` enum and `ActionInfo` struct.
    * `Player.hh`, `Zombie.hh`, `Room.hh`, `Game.hh`: Header files for respective classes, containing declarations and member function prototypes.
* **`src/` Directory:**
    * `Player.cpp`, `Zombie.cpp`, `Room.cpp`, `Game.cpp`: Implementation files for the corresponding classes' member functions.
    * `Item.cpp`, `Action.cpp`: (Potentially empty) Implementation for struct methods if not defined in the header.
    * `main.cpp`: Contains the `main` function, serving as the program's entry point, responsible for creating the `Game` object and calling its `run` method.

## 7. Current Implementation Status (Checklist)

* [x] **Room System:** 6 interconnected rooms, 3x2 layout.
* [x] **Enemy System:** 4 distinct zombie types (Walker, Runner, Bloater, Crawler).
* [x] **Item System:** 7 collectible items (weapons, armor, consumables).
* [x] **Win Condition:** Reaching Room #5.
* [x] **Interaction System:** Number-based menu driven.
* [x] **Memory Management:** Utilizes `std::unique_ptr`.
* [x] **Game Loop:** Complete main loop with win/loss conditions.
* [x] **Project Structure:** Multi-file (`.hh`/`.cpp`) structure.
* [x] **Bonus - Clear Screen:** Implemented.
```
