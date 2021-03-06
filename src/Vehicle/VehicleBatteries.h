#ifndef VEHICLEBATTERIES_H
#define VEHICLEBATTERIES_H

#include <QObject>
#include <FactGroup.h>

#include "MAVLinkProtocol.h"
#include <memory>


class VehicleBatteryFactGroup : public FactGroup
{
    Q_OBJECT

public:
    VehicleBatteryFactGroup(QString const& metaFile, QObject* parent = NULL);

    Q_PROPERTY(Fact* voltage            READ voltage            CONSTANT)
    Q_PROPERTY(Fact* percentRemaining   READ percentRemaining   CONSTANT)
    Q_PROPERTY(Fact* mahConsumed        READ mahConsumed        CONSTANT)
    Q_PROPERTY(Fact* current            READ current            CONSTANT)
    Q_PROPERTY(Fact* temperature        READ temperature        CONSTANT)
    Q_PROPERTY(Fact* cellCount          READ cellCount          CONSTANT)

    Fact* voltage                   (void) { return &_voltageFact; }
    Fact* percentRemaining          (void) { return &_percentRemainingFact; }
    Fact* mahConsumed               (void) { return &_mahConsumedFact; }
    Fact* current                   (void) { return &_currentFact; }
    Fact* temperature               (void) { return &_temperatureFact; }
    Fact* cellCount                 (void) { return &_cellCountFact; }

    void setVoltage          (double  value);
    void setPercentRemaining (int32_t value);
    void setMahConsumed      (int32_t value);
    void setCurrent          (float   value);
    void setTemperature      (double  value);
    void setCellCount        (int32_t value);


    static const char* _voltageFactName;
    static const char* _percentRemainingFactName;
    static const char* _mahConsumedFactName;
    static const char* _currentFactName;
    static const char* _temperatureFactName;
    static const char* _cellCountFactName;

    static const char* _settingsGroup;

    static const double _voltageUnavailable;
    static const int    _percentRemainingUnavailable;
    static const int    _mahConsumedUnavailable;
    static const int    _currentUnavailable;
    static const double _temperatureUnavailable;
    static const int    _cellCountUnavailable;

private:
    Fact            _voltageFact;
    Fact            _percentRemainingFact;
    Fact            _mahConsumedFact;
    Fact            _currentFact;
    Fact            _temperatureFact;
    Fact            _cellCountFact;
};


class VehicleBatteries : public QObject
{
    Q_OBJECT
public:
    struct Battery {
        QString factName;
        FactGroup* factGroup;
    };

    VehicleBatteries(QObject *parent = nullptr);

    Battery battery(int batNum) const;

public slots:
    void handleBatteryStatus (const mavlink_message_t& message);
    void handleSysStatus     (const mavlink_message_t& message);
    void handleBattery2      (const mavlink_message_t& message);

private:
    static char const* _battery1FactGroupName;
    static char const* _battery2FactGroupName;

    std::vector<std::unique_ptr<VehicleBatteryFactGroup>> _batteries;
};

#endif // VEHICLEBATTERIES_H
