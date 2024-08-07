#include "cryptocurrencyproxymodel.h"
#include "cryptocurrencymodel.h"

CryptoCurrencyProxyModel::CryptoCurrencyProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void CryptoCurrencyProxyModel::setSortRoleName(const QString &roleName)
{
    int role = static_cast<int>(CryptoCurrencyModel::Role::MarketCap);
    if (roleName == "24h Change") {
        role = static_cast<int>(CryptoCurrencyModel::Role::ChangeIn24H);
    } else if (roleName == "Name") {
        role = static_cast<int>(CryptoCurrencyModel::Role::Name);
    } else if (roleName == "Price") {
        role = static_cast<int>(CryptoCurrencyModel::Role::Price);
    }

    setSortRole(role);
    sort(0, _order);
}

void CryptoCurrencyProxyModel::setSortOrder(const QString &roleName)
{
    if (roleName == "Ascending") {
        _order = Qt::SortOrder::AscendingOrder;
    } else {
        _order = Qt::SortOrder::DescendingOrder;
    }
    sort(0, _order);
}

bool CryptoCurrencyProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if(sourceModel() == nullptr) {
        return true;
    }

    QVariant leftData = sourceModel()->data(source_left, sortRole());
    QVariant rightData = sourceModel()->data(source_right, sortRole());

    // TODO: add fuzzy compare for qreal
    if (sortRole() == static_cast<int>(CryptoCurrencyModel::Role::ChangeIn24H)) {
        return leftData.toDouble() < rightData.toDouble();
    } else if (sortRole() == static_cast<int>(CryptoCurrencyModel::Role::Name)) {
        return leftData.toString().toLower() < rightData.toString().toLower();
    } else if (sortRole() == static_cast<int>(CryptoCurrencyModel::Role::Price)) {
        return leftData.toString().toLower() < rightData.toString().toLower();
    } else {
        return leftData.toString().toLower() < rightData.toString().toLower();
    }
}
