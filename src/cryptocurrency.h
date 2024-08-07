#pragma once

#include <QString>

struct CryptoCurrency
{
public:
    CryptoCurrency(const QString& id, const QString& image, const QString& name, const QString& ticker,
                   const qreal price, const qreal changeIn24h, const qreal marketCap, const QString& lastUpdatedTime);

    bool operator==(const CryptoCurrency &other) const;
    bool operator!=(const CryptoCurrency &other) const;

    QString id;
    QString logoUrl;
    QString name;
    QString ticker;
    qreal price;
    qreal changeIn24h;
    qreal marketCap;
    QString lastUpdatedTime;
};

using CryptoCurrencyList = QList<CryptoCurrency>;
