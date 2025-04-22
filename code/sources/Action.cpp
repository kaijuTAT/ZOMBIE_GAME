
// ---------- src/Action.cpp ----------
// (如果 ActionInfo 构造函数在头文件中定义，则此文件为空或不存在)
#include "../include/Action.hh" // <<<--- UPDATED INCLUDE

ActionInfo::ActionInfo(ActionType t, int index) : type(t), targetIndex(index) {}

