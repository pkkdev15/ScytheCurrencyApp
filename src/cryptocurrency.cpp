#include "cryptocurrency.h"

CryptoCurrency::CryptoCurrency(const QString &id, const QString &image, const QString &name, const QString &ticker,
                               const qreal price, const qreal changeIn24h, const qreal marketCap, const QString &lastUpdatedTime)
    : id(id), logoUrl(image), name(name), ticker(ticker), price(price), changeIn24h(changeIn24h),
    marketCap(marketCap), lastUpdatedTime(lastUpdatedTime)
{

}

bool CryptoCurrency::operator==(const CryptoCurrency &other) const
{
    return id == other.id && logoUrl == other.logoUrl &&
           name == other.name && ticker == other.ticker && qFuzzyCompare(price, other.price) &&
           qFuzzyCompare(changeIn24h, other.changeIn24h) && qFuzzyCompare(marketCap, other.marketCap) && lastUpdatedTime == other.lastUpdatedTime;
}

bool CryptoCurrency::operator!=(const CryptoCurrency &other) const
{
    return (*this == other) == false;
}
