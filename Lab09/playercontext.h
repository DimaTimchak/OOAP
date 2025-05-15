#ifndef PLAYERCONTEXT_H
#define PLAYERCONTEXT_H


#pragma once
#include <QObject>
#include <QString>
#include <memory>
#include "state.cpp"

class PlayerContext : public QObject {
    Q_OBJECT
public:
    explicit PlayerContext(QObject *parent = nullptr);

    Q_INVOKABLE void setState(const QString &stateName);
    Q_INVOKABLE QString executeAction(const QString &action);

private:
    std::unique_ptr<State> state;
};

#endif // PLAYERCONTEXT_H
