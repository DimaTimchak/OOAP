#pragma once
#include "state.cpp"

class LockedState : public State {
public:
    QString handleAction(const QString &action) override{
        return "Unlock the player first";
    }
};
