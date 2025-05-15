#pragma once
#include "state.cpp"

class LowBatteryState : public State {
public:
    QString handleAction(const QString &action) override{
        return "Charge the device to proceed";
    }
};
