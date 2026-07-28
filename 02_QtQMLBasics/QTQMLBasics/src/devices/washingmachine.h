#ifndef WASHINGMACHINE_H
#define WASHINGMACHINE_H

#include "ismartdevice.h"

class WashingMachine : public ISmartDevice
{
    Q_OBJECT

    // Cycle configurations
    Q_PROPERTY(int spinSpeed READ spinSpeed WRITE setSpinSpeed NOTIFY spinSpeedChanged)
    Q_PROPERTY(int waterTemperature READ waterTemperature WRITE setWaterTemperature NOTIFY waterTemperatureChanged)
    Q_PROPERTY(DeviceEnums::WashCycle washCycle READ washCycle WRITE setWashCycle NOTIFY washCycleChanged)

    // State & Safety
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(bool childLock READ childLock WRITE setChildLock NOTIFY childLockChanged)
    Q_PROPERTY(int timeRemainingMinutes READ timeRemainingMinutes NOTIFY timeRemainingMinutesChanged)

    // Hardware bounds
    Q_PROPERTY(int minSpinSpeed READ getMinSpinSpeed CONSTANT)
    Q_PROPERTY(int maxSpinSpeed READ getMaxSpinSpeed CONSTANT)
    Q_PROPERTY(int minWaterTemp READ getMinWaterTemp CONSTANT)
    Q_PROPERTY(int maxWaterTemp READ getMaxWaterTemp CONSTANT)

public:
    explicit WashingMachine(const QString &name, QObject *parent = nullptr);

    int spinSpeed() const;
    int waterTemperature() const;
    DeviceEnums::WashCycle washCycle() const;

    bool isRunning() const;
    bool childLock() const;
    int timeRemainingMinutes() const;

    // Boundary getters
    static constexpr int minSpinSpeed{0};
    static constexpr int maxSpinSpeed{1400};
    static constexpr int minWaterTemp{20};
    static constexpr int maxWaterTemp{90};

    int getMinSpinSpeed() const { return minSpinSpeed; }
    int getMaxSpinSpeed() const { return maxSpinSpeed; }
    int getMinWaterTemp() const { return minWaterTemp; }
    int getMaxWaterTemp() const { return maxWaterTemp; }

public slots:
    void setSpinSpeed(int rpm);
    void setWaterTemperature(int temp);
    void setWashCycle(DeviceEnums::WashCycle cycle);
    void setChildLock(bool locked);

    // Operational actions
    void startCycle();
    void pauseCycle();
    void stopCycle();

    void togglePower() override;

signals:
    void spinSpeedChanged(int rpm);
    void waterTemperatureChanged(int temp);
    void washCycleChanged(DeviceEnums::WashCycle cycle);
    void isRunningChanged(bool running);
    void childLockChanged(bool locked);
    void timeRemainingMinutesChanged(int minutes);

private:
    int m_spinSpeed;
    int m_waterTemperature;
    DeviceEnums::WashCycle m_washCycle;
    bool m_isRunning;
    bool m_childLock;
    int m_timeRemainingMinutes;

    void updateTimeRemaining(int minutes);
};

#endif //WASHINGMACHINE_H
