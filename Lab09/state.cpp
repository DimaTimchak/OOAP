#pragma once
#include <QString>

class PlayerContext;

class State {
public:
    virtual ~State() = default;
    virtual QString handleAction(const QString &action) = 0;
};
