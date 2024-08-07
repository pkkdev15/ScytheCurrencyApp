import QtQuick

Item {
    id: root

    Rectangle {
        id: loadingScreen
        anchors.fill: parent
        color: "black"
        opacity: 0.3

        Row {
            anchors.centerIn: parent

            Image {
                id: loadingIndicator
                source: "/images/loading_indicator.png"

                RotationAnimation on rotation {
                    from: 0
                    to: 360
                    duration: 1000
                    running: loadingIndicator.visible
                    loops: Animation.Infinite
                }
            }
        }
        // absorb all click events
        MouseArea {
            anchors.fill: parent
        }
    }
}
