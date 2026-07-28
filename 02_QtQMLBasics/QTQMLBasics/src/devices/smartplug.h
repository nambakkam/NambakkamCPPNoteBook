#ifndef SMARTPLUG_H
#define SMARTPLUG_H

#include "ismartdevice.h"

class SmartPlug : public ISmartDevice
{
    Q_OBJECT

    // Real-time energy monitoring
    Q_PROPERTY(double currentPowerWatts READ currentPowerWatts NOTIFY currentPowerWattsChanged)
    Q_PROPERTY(double totalEnergyKWh READ totalEnergyKWh NOTIFY totalEnergyKWhChanged)

    // Timer features
    Q_PROPERTY(int countdownSeconds READ countdownSeconds WRITE setCountdownSeconds NOTIFY countdownSecondsChanged)

    // Safety and limits
    Q_PROPERTY(double overloadThresholdWatts READ overloadThresholdWatts WRITE setOverloadThresholdWatts NOTIFY overloadThresholdWattsChanged)
    Q_PROPERTY(bool isOverloaded READ isOverloaded NOTIFY overloadedStateChanged)

public:
    explicit SmartPlug(const QString &name, QObject *parent = nullptr);

    double currentPowerWatts() const;
    double totalEnergyKWh() const;
    int countdownSeconds() const;
    double overloadThresholdWatts() const;
    bool isOverloaded() const;

public slots:
    void setCountdownSeconds(int seconds);
    void setOverloadThresholdWatts(double watts);

    // Callbacks/Sensors update power consumption
    void updatePowerUsage(double watts, double additionalKWh = 0.0);
    void resetTotalEnergy();

    void togglePower() override;

signals:
    void currentPowerWattsChanged(double watts);
    void totalEnergyKWhChanged(double kWh);
    void countdownSecondsChanged(int seconds);
    void overloadThresholdWattsChanged(double watts);
    void overloadedStateChanged(bool overloaded);

private:
    double m_currentPowerWatts;
    double m_totalEnergyKWh;
    int m_countdownSeconds;
    double m_overloadThresholdWatts;
    bool m_isOverloaded;

    void setOverloaded(bool overloaded);
};

#endif // SMARTPLUG_H