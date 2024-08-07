import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import currencyApp

Window {
    width: 1900
    height: 1200
    visible: true
    title: qsTr("Crypto currency price viewer")

    NavigationBar {
        id: navigationBar

        width: parent.width
        height: 60

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        backgroundColor: appController.lastFetchDataFailed ? "#ffd4da" : "#d6ebff"
        borderColor: appController.lastFetchDataFailed ? "red" : "blue"

        // TODO: change that to pass enum values to c++, not strings
        sortRoleModel: ListModel {
            id: model
            ListElement { text: "Ranking" }
            ListElement { text: "Price" }
            ListElement { text: "24h Change" }
            ListElement { text: "Name" }
        }
        sortOrderModel: ListModel {
                id: sortRoleModel
                ListElement { text: "Ascending" }
                ListElement { text: "Descending" }
        }
        showLoadingScreen: appController.fetchInProgress
        showErrorMessage: appController.lastFetchDataFailed

        onSortOrderChanged: function(sortOrder) {
            // TODO: this one shoudn't be pass as string value, I should use sort role
            // and use it
            cryptoCurrencyProxyModel.setSortOrder(sortOrder)
        }

        onSortRoleChanged: function(sortRole) {
            // TODO: this one shoudn't be pass as string value, I should register enum role
            // and use it
            cryptoCurrencyProxyModel.setSortRoleName(sortRole)
        }

        onUpdateModeChanged: function(updateManually) {
            appController.enableMockedData = updateManually
        }

        onManualUpdateRequested: {
            // TODO: this looks complicated, but it isn't, maybe some of the logic like index mappong can go
            // to C++ side and for the rest create js lib
            let visibleIndexRange = view.getVisibleIndexRange();
            if (visibleIndexRange.lenght === 0) {
                return;
            } else if (visibleIndexRange.lenght === 1) {
                let sourceIdx = cryptoCurrencyProxyModel.mapToSource(cryptoCurrencyProxyModel.index(visibleIndexRange[0], 0));
                cryptoCurrencyModel.updateDataByRandomValue([sourceIdx])
            } else {
                let index1 = visibleIndexRange[Math.floor(Math.random() * visibleIndexRange.length)];
                delete visibleIndexRange[index1]
                let index2 = visibleIndexRange[Math.floor(Math.random() * visibleIndexRange.length)];
                let sourceIdx1 = cryptoCurrencyProxyModel.mapToSource(cryptoCurrencyProxyModel.index(index1, 0));
                let sourceIdx2 = cryptoCurrencyProxyModel.mapToSource(cryptoCurrencyProxyModel.index(index2, 0));
                cryptoCurrencyModel.updateDataByRandomValue([sourceIdx1, sourceIdx2])
            }
        }
    }

    Rectangle {
        id: contentView
        width: parent.width
        anchors {
            top: navigationBar.bottom
            bottom: parent.bottom
        }
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightblue" }
            GradientStop { position: 1.0; color: "darkblue" }
        }

        ListView {
            id: view
            anchors.fill: parent
            anchors {
                leftMargin: 50
                rightMargin: 50
                topMargin: 10
            }
            model: CryptoCurrencyProxyModel {
                id: cryptoCurrencyProxyModel
                sourceModel: cryptoCurrencyModel

                onDataChanged: function(topLeft, bottomLeft) {
                    // TODO: I think there should be better way to implement that
                    // maybe by adding delegate in C++?
                    var item = view.itemAtIndex(topLeft.row)
                    if (item && item.runDelegateBackgroundAnimation === true) {
                        // reset animation trigger
                        item.runDelegateBackgroundAnimation = false
                    }
                    item.runDelegateBackgroundAnimation = true
                }
            }
            clip: true

            ScrollBar.vertical: ScrollBar {
                active: true
                width: 20
            }
            delegate: CurrencyDelegate {
                width: parent ? parent.width : 0
                height: 100
                imageSource: model.iamgeUrl
                currencyName: model.name + " " + model.ticker
                currencyPrice: "Current price: " + model.price
                currencyMarketCap: "Market cap: " + model.marketCap
                currencyChangeIn24H: model.changeIn24H + "%"
                currencyChangeIn24HColor: model.changeIn24H > 0 ? "green" : "red"
                currencyLastUpdate: "Last update: " + model.lastUpdateTime
            }

            function getVisibleIndexRange() {
                var centerX = view.x + view.width * 0.5;
                var offset = 50;
                var topIdx = indexAt(centerX, view.y + view.contentY + offset);
                var bottomIdx = indexAt(centerX, view.y + view.contentY + view.height - offset);
                if (topIdx === -1 || bottomIdx === -1) {
                    return []
                }
                return [...Array(bottomIdx - topIdx + 1).keys()].map(i => i + topIdx);
            }
        }
    }
}
