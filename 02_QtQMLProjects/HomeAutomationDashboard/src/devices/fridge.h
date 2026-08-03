#ifndef FRIDGE_H
#define FRIDGE_H

#include "ismartdevice.h"

class Fridge : public ISmartDevice
{
    Q_OBJECT

    // Temperature properties
    Q_PROPERTY(int fridgeTemperature READ fridgeTemperature WRITE setFridgeTemperature NOTIFY fridgeTemperatureChanged)
    Q_PROPERTY(int freezerTemperature READ freezerTemperature WRITE setFreezerTemperature NOTIFY freezerTemperatureChanged)

    // Feature toggles
    Q_PROPERTY(bool rapidCool READ rapidCool WRITE setRapidCool NOTIFY rapidCoolChanged)
    Q_PROPERTY(bool superFreeze READ superFreeze WRITE setSuperFreeze NOTIFY superFreezeChanged)

    // Status properties
    Q_PROPERTY(bool isDoorOpen READ isDoorOpen NOTIFY doorStateChanged)

    // Hardware bounds
    Q_PROPERTY(int lowestFridgeTemp READ getLowestFridgeTemp CONSTANT)
    Q_PROPERTY(int highestFridgeTemp READ getHighestFridgeTemp CONSTANT)
    Q_PROPERTY(int lowestFreezerTemp READ getLowestFreezerTemp CONSTANT)
    Q_PROPERTY(int highestFreezerTemp READ getHighestFreezerTemp CONSTANT)

public:
    explicit Fridge(const QString &name, QObject *parent = nullptr);

    int fridgeTemperature() const;
    int freezerTemperature() const;
    bool rapidCool() const;
    bool superFreeze() const;
    bool isDoorOpen() const;

    // Boundary getters
    static constexpr int lowestFridgeTemp{1};
    static constexpr int highestFridgeTemp{7};
    static constexpr int lowestFreezerTemp{-24};
    static constexpr int highestFreezerTemp{-14};

    int getLowestFridgeTemp() const { return lowestFridgeTemp; }
    int getHighestFridgeTemp() const { return highestFridgeTemp; }
    int getLowestFreezerTemp() const { return lowestFreezerTemp; }
    int getHighestFreezerTemp() const { return highestFreezerTemp; }

public slots:
    void setFridgeTemperature(int temp);
    void setFreezerTemperature(int temp);
    void setRapidCool(bool enabled);
    void setSuperFreeze(bool enabled);
    void setDoorOpen(bool open); // Called by internal/hardware sensors

    void togglePower() override;

signals:
    void fridgeTemperatureChanged(int temp);
    void freezerTemperatureChanged(int temp);
    void rapidCoolChanged(bool enabled);
    void superFreezeChanged(bool enabled);
    void doorStateChanged(bool open);

private:
    int m_fridgeTemperature;
    int m_freezerTemperature;
    bool m_rapidCool;
    bool m_superFreeze;
    bool m_isDoorOpen;
};

#endif // FRIDGE_H