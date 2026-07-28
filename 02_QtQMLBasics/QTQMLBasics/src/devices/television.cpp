#include "television.h"

Television::Television(const QString &name, QObject *parent)
    : ISmartDevice(name, DeviceEnums::Television, DeviceEnums::Off, parent)
    , m_volume(20)
    , m_isMuted(false)
    , m_channelNumber(1)
    , m_inputSource(DeviceEnums::HDMI1)
{
}

int Television::volume() const
{
    return m_volume;
}

void Television::setVolume(int volume)
{
    const int clampedVolume = qBound(minVolume, volume, maxVolume);
    if (m_volume != clampedVolume) {
        m_volume = clampedVolume;
        emit volumeChanged(m_volume);
        
        // Unmute automatically when modifying volume
        if (m_isMuted && m_volume > 0) {
            setMuted(false);
        }
    }
}

bool Television::isMuted() const
{
    return m_isMuted;
}

void Television::setMuted(bool muted)
{
    if (m_isMuted != muted) {
        m_isMuted = muted;
        emit mutedChanged(m_isMuted);
    }
}

int Television::channelNumber() const
{
    return m_channelNumber;
}

void Television::setChannelNumber(int channel)
{
    if (channel < 1) return; // Prevent negative/zero channels

    if (m_channelNumber != channel) {
        m_channelNumber = channel;
        emit channelNumberChanged(m_channelNumber);
    }
}

DeviceEnums::InputSource Television::inputSource() const
{
    return m_inputSource;
}

void Television::setInputSource(DeviceEnums::InputSource source)
{
    if (m_inputSource != source) {
        m_inputSource = source;
        emit inputSourceChanged(m_inputSource);
    }
}

void Television::volumeUp()
{
    setVolume(m_volume + 1);
}

void Television::volumeDown()
{
    setVolume(m_volume - 1);
}

void Television::channelUp()
{
    setChannelNumber(m_channelNumber + 1);
}

void Television::channelDown()
{
    if (m_channelNumber > 1) {
        setChannelNumber(m_channelNumber - 1);
    }
}

void Television::togglePower()
{
    auto newState = (getDeviceState() == DeviceEnums::On) 
                    ? DeviceEnums::Off 
                    : DeviceEnums::On;
    setDeviceState(newState);
}