// ---------- src/main.cpp ----------
#include "../include/Game.hh" // <<<--- UPDATED INCLUDE
#include <iostream>
#include <exception> // For std::exception
#include <limits>    // For std::numeric_limits

int main() {
    try {
        Game zomboidGame; // 创建游戏实例 CREAT A GAME INSTANCE
        zomboidGame.run();   // 运行游戏主循环 RUNE THE GAME MAIN LOOP
    } catch (const std::exception& e) {
        // 捕获并报告标准异常 CAPTURE AND REPORT THE STANDERD ERROR 
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        // 在退出前暂停，以便用户看到错误信息 PAUSE BEFORE EXIT, SO THAT THE USER COULD READ THE ERROR INFO
        std::cerr << "Press Enter to exit...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区 CLEAR THE 
        std::cin.get(); // 等待回车 WAIT FOR THE "ENTER"
        return 1; // 返回错误代码 RETURN THE ERROR CODE
    } catch (...) {
         // 捕获所有其他未知类型的异常 CAPTURE ALL THE OTHER UNKNOWN TYPE ERROR
         std::cerr << "An unknown error occurred." << std::endl;
         // 在退出前暂停 PAUESE BEFORE EXIT
         std::cerr << "Press Enter to exit...";
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区 CLEAR THE 
         std::cin.get(); // 等待回车 WAIT FOR THE "ENTER"
         return 1; // 返回错误代码 RETURN THE ERROR CODE
    }
    return 0; // 程序正常结束 THE PROGRAM END IN A NORMAL STATUS
}
