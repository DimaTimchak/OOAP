import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Radio Player"

    property string message: "Player Unlocked"

    Column {
        spacing: 10
        anchors.centerIn: parent

        // Кнопки вибору стану
        Row {
            spacing: 5
            Button {
                text: "Unlocked"
                onClicked: playerContext.setState("unlocked")
            }
            Button {
                text: "Locked"
                onClicked: playerContext.setState("locked")
            }
            Button {
                text: "Low Battery"
                onClicked: playerContext.setState("lowbattery")
            }
        }

        // Кнопки керування плеєром
        Row {
            spacing: 5
            Button { text: "Play"; onClicked: message = playerContext.executeAction("Play") }
            Button { text: "Stop"; onClicked: message = playerContext.executeAction("Stop") }
            Button { text: "Pause"; onClicked: message = playerContext.executeAction("Pause") }
            Button { text: "Repeat"; onClicked: message = playerContext.executeAction("Repeat") }
        }

        // Повідомлення
        Text {
            text: message
            font.pixelSize: 20
            color: "blue"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
