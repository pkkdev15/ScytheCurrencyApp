#pragma once

#include "cryptocurrencymodel.h"

#include <QObject>
#include <QThread>
#include <QPointer>
#include <QTimer>

class AppController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(bool fetchInProgress READ fetchInProgress NOTIFY fetchInProgressChanged FINAL)
    Q_PROPERTY(bool lastFetchDataFailed READ lastFetchDataFailed WRITE setLastFetchDataFailed NOTIFY lastFetchDataFailedChanged FINAL)
    Q_PROPERTY(bool enableMockedData READ enableMockedData WRITE setEnableMockedData NOTIFY enableMockedDataChanged FINAL)

    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    CryptoCurrencyModel* model() const;
    void getCurrencyData();

    bool fetchInProgress() const;
    bool lastFetchDataFailed() const;

    bool enableMockedData() const;
    void setEnableMockedData(const bool value);

signals:
    void fetchInProgressChanged();
    void lastFetchDataFailedChanged();
    void enableMockedDataChanged();

private:
    void setLastFetchDataFailed(const bool value);

    QPointer<CryptoCurrencyModel> _model;
    QPointer<QThread> _workerThread;
    QTimer _refreshTimer;
    bool _lastFetchDataFailed{false};
    bool _enableMockedData{false};
    const int REFRESH_INTERVAL{3000};
};
