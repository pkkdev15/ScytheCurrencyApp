#include "coingeckodataworker.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>

namespace {
const inline auto ID = QStringLiteral("id");
const inline auto IMAGE = QStringLiteral("image");
const inline auto NAME = QStringLiteral("name");
const inline auto TICKER = QStringLiteral("symbol");
const inline auto PRICE = QStringLiteral("current_price");
const inline auto CHANGE_IN_24H = QStringLiteral("price_change_percentage_24h");
const inline auto MARKET_CAP = QStringLiteral("market_cap");
const inline auto LAST_UPDATE_TIME = QStringLiteral("last_updated");
}

CoinGeckoDataWorker::CoinGeckoDataWorker(QObject *parent)
    : QObject(parent)
    , _url("https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd")
{
    connect(&_networkManager, &QNetworkAccessManager::finished,
            this, &CoinGeckoDataWorker::onReqeustFinished);
}

void CoinGeckoDataWorker::onReqeustFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QThread::msleep(3000); // just to demonstrate loading indicator in UI
        emit error(reply->error(), reply->errorString());
        reply->deleteLater();
        QThread::msleep(3000); // just to demonstrate loading indicator in UI
        emit finished();
        return;
    }

    QThread::msleep(3000); // just to demonstrate loading indicator in UI

    const auto& responseData = reply->readAll();
    const auto& jsonDoc = QJsonDocument::fromJson(responseData);
    const auto& jsonArray = jsonDoc.array();

    // TODO: Add validation for json data from replay (properties check etc)
    CryptoCurrencyList items;
    for (const QJsonValue &value : jsonArray) {
        QVariantMap properties;
        QJsonObject object = value.toObject();
        for (const QString &key : object.keys()) {
            properties.insert(key, object.value(key).toVariant());
        }
        const auto item = CryptoCurrency(properties[ID].toString(),
                                        properties[IMAGE].toString(),
                                        properties[NAME].toString(),
                                        properties[TICKER].toString(),
                                        properties[PRICE].toDouble(),
                                        properties[CHANGE_IN_24H].toDouble(),
                                        properties[MARKET_CAP].toDouble(),
                                        properties[LAST_UPDATE_TIME].toString());
        items.append(item);
    }
    emit newDataAvailable(items);
    reply->deleteLater();
    emit finished();
}

void CoinGeckoDataWorker::fetch()
{
    qInfo() << "Fetching data...";
    QNetworkRequest request(_url);
    _networkManager.get(request);
}
