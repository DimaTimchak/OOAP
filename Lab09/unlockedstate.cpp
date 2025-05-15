#pragma once
#include "state.cpp"

class UnlockedState : public State {
public:
    QString handleAction(const QString &action) override{
        return action + " action executed";
    }
};
