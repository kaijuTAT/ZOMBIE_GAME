// ---------- include/Action.hh ---------- // <<<--- UPDATED FILENAME
#ifndef ACTION_HH // <<<--- UPDATED GUARD
#define ACTION_HH // <<<--- UPDATED GUARD

// 定义可能的玩家动作类型
enum class ActionType { MOVE, PICKUP, ATTACK, USE_ITEM, VIEW_INVENTORY, VIEW_STATUS, INVALID };

// 存储玩家可执行动作的详细信息
struct ActionInfo {
    ActionType type = ActionType::INVALID;
    int targetIndex = -1; // Can represent direction index, item index, or zombie index

    ActionInfo(ActionType t = ActionType::INVALID, int index = -1);
};

#endif // ACTION_HH // <<<--- UPDATED GUARD
