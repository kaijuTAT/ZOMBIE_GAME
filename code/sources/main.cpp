// ---------- src/main.cpp ----------
#include "../include/Game.hh" // Include Game header
#include <iostream>
#include <exception> // For std::exception
#include <limits>    // <<<--- ADDED INCLUDE for std::numeric_limits

int main() {
    try {
        Game zomboidGame; // 创建游戏实例
        zomboidGame.run();   // 运行游戏主循环
    } catch (const std::exception& e) {
        // 捕获并报告标准异常
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        // 在退出前暂停，以便用户看到错误信息
        std::cerr << "Press Enter to exit...";
        // <<<--- Requires <limits> --- >>>
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区
        std::cin.get(); // 等待回车
        return 1; // 返回错误代码
    } catch (...) {
         // 捕获所有其他未知类型的异常
         std::cerr << "An unknown error occurred." << std::endl;
         // 在退出前暂停
         std::cerr << "Press Enter to exit...";
         // <<<--- Requires <limits> --- >>>
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区
         std::cin.get(); // 等待回车
         return 1; // 返回错误代码
    }
    return 0; // 程序正常结束
}
