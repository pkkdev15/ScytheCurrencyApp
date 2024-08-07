import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property alias backgroundColor: background.color
    property color borderColor
    property alias showLoadingScreen: loadingScreen.visible

    property alias sortOrderModel: sortOrderComboBox.model
    property alias sortRoleModel: sortRoleComboBox.model
    property alias showErrorMessage: errorMessageText.visible

    signal sortOrderChanged(string sortOrder)
    signal sortRoleChanged(string sortRole)
    signal updateModeChanged(bool updateManually)
    signal manualUpdateRequested()

    Rectangle {
        id: background
        anchors.fill: parent
        border {
            width: 4
            color: root.borderColor
        }

        RowLayout {
            spacing: 10
            anchors {
                fill: parent
                leftMargin: 50
                rightMargin: 50
                topMargin: 5
                bottomMargin: 5
            }

            Row {
                spacing: 10
                Layout.alignment: Qt.AlignHCenter

                ComboBox {
                    id: sortRoleComboBox
                    Layout.alignment: Qt.AlignLeft

                    onCurrentIndexChanged: {
                        let currentIdx = sortRoleComboBox.currentIndex;
                        sortRoleChanged(sortRoleComboBox.model.get(currentIdx).text)
                    }
                }

                ComboBox {
                    id: sortOrderComboBox
                    Layout.alignment: Qt.AlignLeft

                    onCurrentIndexChanged: {
                        let currentIdx = sortOrderComboBox.currentIndex;
                        sortOrderChanged(sortOrderComboBox.model.get(currentIdx).text)
                    }
                }

                CheckBox {
                    id: manualUpdateCheckbox
                    text: "Use random data"

                    onCheckStateChanged: {
                        updateModeChanged(checked)
                    }
                }

                Button {
                    text: "Update random records on screen"
                    visible: manualUpdateCheckbox.checked

                    onClicked: {
                        manualUpdateRequested()
                    }
                }
            }

            Text {
                id: errorMessageText
                Layout.alignment: Qt.AlignRight
                text: "Cannot update currency data, current list may be outdated!";
                color: "red"
                font.pointSize: 15
                elide: Text.ElideRight
            }
        }

        LoadingScreen {
            id: loadingScreen

            anchors.fill: parent
        }
    }
}
