#include "television.h"

Television::Television(const QString &deviceId, const QString &name, QObject *parent)
    : ISmartDevice(deviceId, name, DeviceEnums::Television, false, parent)
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

void Television::updateState(const QJsonObject &state)
{
    if (state.contains("powerState")) {
        setPowerState(state["powerState"].toBool());
    }
    if (state.contains("volume")) {
        setVolume(state["volume"].toInt());
    }
    if (state.contains("isMuted")) {
        setMuted(state["isMuted"].toBool());
    }
    if (state.contains("channelNumber")) {
        setChannelNumber(state["channelNumber"].toInt());
    }
    if (state.contains("inputSource")) {
        setInputSource(static_cast<DeviceEnums::InputSource>(state["inputSource"].toInt()));
    }
}

QJsonObject Television::currentState() const
{
    QJsonObject state;
    state["deviceId"] = getDeviceId();
    state["deviceName"] = getDeviceName();
    state["deviceType"] = static_cast<int>(getDeviceType());
    state["powerState"] = getPowerState();
    state["volume"] = m_volume;
    state["isMuted"] = m_isMuted;
    state["channelNumber"] = m_channelNumber;
    state["inputSource"] = static_cast<int>(m_inputSource);
    return state;
}
