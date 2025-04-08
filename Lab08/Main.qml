import QtQuick
import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Mediator Pattern in QML"

    Column {
        spacing: 15
        padding: 30
        anchors.centerIn: parent

        Repeater {
            model: 4
            delegate: TextField {
                width: 300
                placeholderText: "Enter text..."

                text: textMediator.text
                onTextEdited: textMediator.updateText(text)
            }
        }
    }
}

