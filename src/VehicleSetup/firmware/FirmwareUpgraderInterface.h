#ifndef FIRMWAREUPGRADERINTERFACE_H
#define FIRMWAREUPGRADERINTERFACE_H

#include <QObject>
#include "upgraders/FlasherParameters.h"
#include <memory>

class FirmwareUpgrader : public QObject
{
    Q_OBJECT
public:
    enum FinishStatus {
        Succeed = 1,
        Cancelled = 0,
        Failed = -1
    };
    Q_ENUM(FinishStatus)

    enum LogMsgType {
        Info = 0,
        Warning,
        Error
    };
    Q_ENUM(LogMsgType)

    static std::unique_ptr<FirmwareUpgrader> instance(void);
    static void registerMetatypes(void) {
        qRegisterMetaType<LogMsgType>("FirmwareUpgrader::LogMsgType");
        qRegisterMetaType<FinishStatus>("FirmwareUpgrader::FinishStatus");
    }

    virtual ~FirmwareUpgrader(void);

    virtual bool deviceAvailable(void) const = 0;

signals:
    void deviceInitializationStarted(void);

    void deviceInitialized (bool status);
    void deviceFlashed     (bool status);
    void cancelled         (void);

    void progressChanged(uint value);
    void firmwareVersionAvailable(QString const& version);

    void errorMessageReceived (QString const& msg);
    void infoMessageReceived  (QString const& msg);
    void warnMessageReceived  (QString const& msg);

public slots:
    virtual void initializeDevice(void)  = 0;
    virtual void flash(FlasherParameters const& image) = 0;
    virtual void cancel(void) = 0;

protected:
    explicit FirmwareUpgrader(QObject* parent = NULL);

};

#endif // FIRMWAREUPGRADERINTERFACE_H
