#include "playercontext.h"
#include "unlockedstate.cpp"
#include "lockedstate.cpp"
#include "lowbatterystate.cpp"

PlayerContext::PlayerContext(QObject *parent) : QObject(parent) {
    state = std::make_unique<UnlockedState>();
}

void PlayerContext::setState(const QString &stateName) {
    if (stateName == "unlocked") {
        state = std::make_unique<UnlockedState>();
    } else if (stateName == "locked") {
        state = std::make_unique<LockedState>();
    } else if (stateName == "lowbattery") {
        state = std::make_unique<LowBatteryState>();
    }
}

QString PlayerContext::executeAction(const QString &action) {
    return state->handleAction(action);
}
