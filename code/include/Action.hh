
// ---------- include/Action.hh ----------
#ifndef ACTION_HH
#define ACTION_HH

/**
 * @file Action.hh
 * @brief Defines structures and enums related to player actions within the game menu.
 */

// 定义可能的玩家动作类型
enum class ActionType { MOVE, PICKUP, ATTACK, USE_ITEM, VIEW_INVENTORY, VIEW_STATUS, INVALID };

// 存储玩家可执行动作的详细信息
struct ActionInfo {
    ActionType type = ActionType::INVALID;
    int targetIndex = -1; // Can represent direction index, item index, or zombie index

    // Constructor
    ActionInfo(ActionType t = ActionType::INVALID, int index = -1);

    // --- Canonical Form (Rule of Zero applies) ---
    ~ActionInfo() = default;
    ActionInfo(const ActionInfo& other) = default;
    ActionInfo& operator=(const ActionInfo& other) = default;
    ActionInfo(ActionInfo&& other) noexcept = default;
    ActionInfo& operator=(ActionInfo&& other) noexcept = default;
};

#endif // ACTION_HH

