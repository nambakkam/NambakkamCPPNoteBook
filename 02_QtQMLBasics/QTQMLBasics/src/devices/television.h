#ifndef TELEVISION_H
#define TELEVISION_H

#include "ismartdevice.h"

class Television : public ISmartDevice
{
    Q_OBJECT

    // Audio & Channel
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool isMuted READ isMuted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(int channelNumber READ channelNumber WRITE setChannelNumber NOTIFY channelNumberChanged)
    
    // Source Selection
    Q_PROPERTY(DeviceEnums::InputSource inputSource READ inputSource WRITE setInputSource NOTIFY inputSourceChanged)

    // Hardware bounds
    Q_PROPERTY(int minVolume READ getMinVolume CONSTANT)
    Q_PROPERTY(int maxVolume READ getMaxVolume CONSTANT)

public:
    explicit Television(const QString &name, QObject *parent = nullptr);

    int volume() const;
    bool isMuted() const;
    int channelNumber() const;
    DeviceEnums::InputSource inputSource() const;

    // Boundary getters
    static constexpr int minVolume{0};
    static constexpr int maxVolume{100};

    int getMinVolume() const { return minVolume; }
    int getMaxVolume() const { return maxVolume; }

public slots:
    void setVolume(int volume);
    void setMuted(bool muted);
    void setChannelNumber(int channel);
    void setInputSource(DeviceEnums::InputSource source);

    // Convenience slots for UI buttons
    void volumeUp();
    void volumeDown();
    void channelUp();
    void channelDown();

    void togglePower() override;

signals:
    void volumeChanged(int volume);
    void mutedChanged(bool muted);
    void channelNumberChanged(int channel);
    void inputSourceChanged(DeviceEnums::InputSource source);

private:
    int m_volume;
    bool m_isMuted;
    int m_channelNumber;
    DeviceEnums::InputSource m_inputSource;
};

#endif // TELEVISION_H