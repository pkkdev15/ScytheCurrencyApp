#include "cryptocurrencymodel.h"
#include <QRandomGenerator>

CryptoCurrencyModel::CryptoCurrencyModel(QObject* parent)
    : QAbstractListModel(parent)
{

}

int CryptoCurrencyModel::itemIndex(const QString &id)
{
    int result = -1;
    for (int idx = 0; idx < _items.size(); ++idx) {
        if (_items[idx].id == id) {
            result = idx;
            break;
        }
    }
    return result;
}

void CryptoCurrencyModel::reload(const CryptoCurrencyList &items)
{
    if (_items.isEmpty()) {
        beginResetModel();
        _items = items;
        endResetModel();
    } else {
        for (const CryptoCurrency &item : items) {
            const int idx = itemIndex(item.id);
            if (idx != -1) {
                const auto& currentItem = _items[idx];
                if (currentItem != item) {
                    _items.replace(idx, item);
                    emit dataChanged(index(idx), index(idx));
                }
            } else {
                beginInsertRows({}, _items.size(), _items.size());
                _items.append(item);
                endInsertRows();
            }
        }
    }
    qInfo() << "Model reload finished";
}

void CryptoCurrencyModel::updateDataByRandomValue(const QModelIndexList& indexes)
{
    // TODO: better way would be to just implement QAbstractListModel::setData, but for
    // this purpose and luck of time this should be enough
    for (const auto& idx : indexes) {
        if (idx.isValid()) {
            auto& item = _items[idx.row()];
            const int randomFactor = QRandomGenerator::global()->bounded(0, 2) > 0 ? 1 : -1;
            const auto change = item.price * 0.02 * randomFactor;
            item.price = item.price + change;
            emit dataChanged(idx, idx);
        }
    }
}

int CryptoCurrencyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

QVariant CryptoCurrencyModel::data(const QModelIndex &index, int role) const
{
    if (checkIndex(index) == false) {
        return {};
    }

    const auto row = index.row();
    const auto enumRole = static_cast<Role>(role);

    switch (enumRole) {
    case Role::Id:
        return _items.at(row).id;
        break;
    case Role::ImageUrl:
        return _items.at(row).logoUrl;
        break;
    case Role::Name:
        return _items.at(row).name;
        break;
    case Role::Ticker:
        return _items.at(row).ticker;
        break;
    case Role::Price:
        return _items.at(row).price;
        break;
    case Role::ChangeIn24H:
        return _items.at(row).changeIn24h;
        break;
    case Role::MarketCap:
        return _items.at(row).marketCap;
        break;
    case Role::LastUpdateTime:
        return _items.at(row).lastUpdatedTime;
        break;
    default:
        break;
    }

    return {};
}

QHash<int, QByteArray> CryptoCurrencyModel::roleNames() const
{
    static const QHash<int, QByteArray> result {
        { static_cast<int>(Role::Id), "id" },
        { static_cast<int>(Role::ImageUrl), "iamgeUrl" },
        { static_cast<int>(Role::Name), "name" },
        { static_cast<int>(Role::Ticker), "ticker" },
        { static_cast<int>(Role::Price), "price" },
        { static_cast<int>(Role::ChangeIn24H), "changeIn24H" },
        { static_cast<int>(Role::MarketCap), "marketCap" },
        { static_cast<int>(Role::LastUpdateTime), "lastUpdateTime" }
    };
    return result;
}
