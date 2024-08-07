#pragma once

#include "cryptocurrency.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CoinGeckoDataWorker : public QObject
{
    Q_OBJECT
public:
    CoinGeckoDataWorker(QObject *parent = nullptr);

public slots:
    void onReqeustFinished(QNetworkReply *reply);
    void fetch();

signals:
    void newDataAvailable(const CryptoCurrencyList& data);
    void error(const QNetworkReply::NetworkError error, const QString& message);
    void finished();

private:
    QNetworkAccessManager _networkManager;
    const QUrl _url;
};
