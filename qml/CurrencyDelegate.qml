import QtQuick
import QtQuick.Layouts
import currencyApp

Item {
    id: root

    property alias imageSource: currencyImage.source
    property alias currencyName: currencyName.text
    property alias currencyPrice: currencyPrice.text
    property alias currencyMarketCap: currencyMarketCap.text
    property alias currencyChangeIn24H: currencyChangeIn24H.text
    property alias currencyChangeIn24HColor: currencyChangeIn24H.color
    property alias currencyLastUpdate: currencyLastUpdate.text
    property bool runDelegateBackgroundAnimation: false

    Canvas {
        id: canvas
        anchors.fill: parent
        antialiasing: true

        property color backroundColor: "white"

        onPaint: {
            var padding = 5;
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.lineWidth = 3
            ctx.strokeStyle = "blue"
            ctx.beginPath()
            ctx.moveTo(padding, padding)
            var one_tird_height = Math.floor((height - padding / 3) / 3);
            ctx.lineTo(width - one_tird_height - padding, padding)
            ctx.lineTo(width - padding, one_tird_height)
            ctx.lineTo(width - padding, height - padding)
            ctx.lineTo(one_tird_height, height - padding)
            ctx.lineTo(padding, Math.floor((height- padding) * 2/3) )
            ctx.lineTo(padding, padding)
            ctx.fillStyle = backroundColor;
            ctx.fill()
        }

        RowLayout {
            anchors.centerIn: parent
            spacing: 10

            Image {
                id: currencyImage
                height: 50
                width: 50
                sourceSize.width: 50
                sourceSize.height: 50
                fillMode: Image.PreserveAspectFit
            }

            Column {
                Text {
                    id: currencyName
                }
                Text {
                    id: currencyPrice
                }
                Text {
                    id: currencyMarketCap
                }
                Row {
                    spacing: 0
                    Text {
                        text: "24h: ";
                    }
                    Text {
                        id: currencyChangeIn24H
                    }
                }
                Text {
                    id: currencyLastUpdate
                }
            }
        }

        onBackroundColorChanged: {
            requestPaint()
        }
    }

    SequentialAnimation {
        id: animation
        ColorAnimation {
            target: canvas
            property: "backroundColor"
            from: "white"
            to: "lightblue"
            duration: 500
        }
        ColorAnimation {
            target: canvas
            property: "backroundColor"
            from: "lightblue"
            to: "white"
            duration: 500
        }

        onFinished: {
            runDelegateBackgroundAnimation = false
        }
    }

    onRunDelegateBackgroundAnimationChanged: {
        if (runDelegateBackgroundAnimation) {
            animation.restart()
        }
    }
}
