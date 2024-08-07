#include "appcontroller.h"
#include "coingeckodataworker.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
    , _model(new CryptoCurrencyModel(this))
{
    connect(&_refreshTimer, &QTimer::timeout,
            this, &AppController::getCurrencyData);

    _refreshTimer.setTimerType(Qt::TimerType::VeryCoarseTimer);
    _refreshTimer.setInterval(REFRESH_INTERVAL);
    _refreshTimer.start();
}

AppController::~AppController()
{
    if (_workerThread) {
        _workerThread->quit();
        _workerThread->wait();
    }
}

CryptoCurrencyModel *AppController::model() const
{
    return _model;
}

bool AppController::fetchInProgress() const
{
    return _workerThread && _workerThread->isRunning();
}

bool AppController::lastFetchDataFailed() const
{
    return _lastFetchDataFailed;
}

void AppController::setLastFetchDataFailed(const bool value)
{
    if (_lastFetchDataFailed != value) {
        _lastFetchDataFailed = value;
        emit lastFetchDataFailedChanged();
    }
}

bool AppController::enableMockedData() const
{
    return _enableMockedData;
}

void AppController::setEnableMockedData(const bool value)
{
    if (_enableMockedData != value) {
        _enableMockedData = value;
        emit enableMockedDataChanged();

        // TODO: move it from setter to separate function
        if (value) {
            _refreshTimer.stop();
        } else {
            _refreshTimer.start();
        }
    }
}

void AppController::getCurrencyData()
{
    if (_workerThread && _workerThread->isRunning()) {
        return;
    }

    if (_workerThread.isNull()) {
        _workerThread = new QThread;
    }

    const auto coinGeckoDataWorker = new CoinGeckoDataWorker;
    coinGeckoDataWorker->moveToThread(_workerThread);

    // TODO: get rid of lambdas from there

    connect(coinGeckoDataWorker, &CoinGeckoDataWorker::newDataAvailable, [this](const CryptoCurrencyList& data){
        qWarning() << "Featch data succeeded";
        setLastFetchDataFailed(false);
        _model->reload(data);
    });
    connect(coinGeckoDataWorker, &CoinGeckoDataWorker::error,
            this, [this](const QNetworkReply::NetworkError error, const QString& message){
        qWarning() << "Featch data error" << error << message;
        setLastFetchDataFailed(true);
    });
    connect(coinGeckoDataWorker, &CoinGeckoDataWorker::finished,
            _workerThread, &QThread::quit);

    connect(_workerThread, &QThread::finished, this, [this, coinGeckoDataWorker](){
        coinGeckoDataWorker->deleteLater();
        _workerThread->deleteLater();
        emit fetchInProgressChanged();
    });
    connect(_workerThread, &QThread::started, this, [this, coinGeckoDataWorker](){
        emit fetchInProgressChanged();
        coinGeckoDataWorker->fetch();
    });
    _workerThread->start();
}
