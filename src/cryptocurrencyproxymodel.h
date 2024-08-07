#pragma once

#include <QSortFilterProxyModel>
#include <qqml.h>

class CryptoCurrencyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    CryptoCurrencyProxyModel(QObject *parent = nullptr);

public slots:
    void setSortRoleName(const QString &roleName);
    void setSortOrder(const QString &roleName);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

private:
    Qt::SortOrder _order {Qt::SortOrder::AscendingOrder};
};
