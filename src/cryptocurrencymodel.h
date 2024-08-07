#pragma once

#include <QString>
#include <QAbstractListModel>
#include <cryptocurrency.h>
#include <qqml.h>

class CryptoCurrencyModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum class Role {
        Id = Qt::ItemDataRole::UserRole + 1,
        ImageUrl,
        Name,
        Ticker,
        Price,
        ChangeIn24H,
        MarketCap,
        LastUpdateTime
    };

    explicit CryptoCurrencyModel(QObject* parent=nullptr);

    int rowCount(const QModelIndex &parent) const final;
    QVariant data(const QModelIndex &index, int role) const final;
    QHash<int, QByteArray> roleNames() const final;

    void reload(const CryptoCurrencyList& items);

public slots:
    void updateDataByRandomValue(const QModelIndexList& indexes);

private:
    int itemIndex(const QString& id);

    QList<CryptoCurrency> _items;
};
