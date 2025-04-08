#ifndef TEXTMEDIATOR_H
#define TEXTMEDIATOR_H

#pragma once
#include <QObject>

class TextMediator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged)

public:
    explicit TextMediator(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void updateText(const QString& newText) {
        if (newText != m_text) {
            m_text = newText;
            emit textChanged();
        }
    }

    QString text() const { return m_text; }

signals:
    void textChanged();

private:
    QString m_text;
};

#endif // TEXTMEDIATOR_H
