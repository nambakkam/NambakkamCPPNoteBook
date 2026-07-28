#include "securitycamera.h"

SecurityCamera::SecurityCamera(const QString &name, QObject *parent)
    : ISmartDevice(name, DeviceEnums::SecurityCamera, DeviceEnums::On, parent) // Cameras default to On
    , m_isStreaming(false)
    , m_isRecording(false)
    , m_nightVisionEnabled(true)
    , m_motionDetectionEnabled(true)
    , m_motionSensitivity(50)
{
}

bool SecurityCamera::isStreaming() const
{
    return m_isStreaming;
}

bool SecurityCamera::isRecording() const
{
    return m_isRecording;
}

bool SecurityCamera::nightVisionEnabled() const
{
    return m_nightVisionEnabled;
}

void SecurityCamera::setNightVisionEnabled(bool enabled)
{
    if (m_nightVisionEnabled != enabled) {
        m_nightVisionEnabled = enabled;
        emit nightVisionEnabledChanged(m_nightVisionEnabled);
    }
}

bool SecurityCamera::motionDetectionEnabled() const
{
    return m_motionDetectionEnabled;
}

void SecurityCamera::setMotionDetectionEnabled(bool enabled)
{
    if (m_motionDetectionEnabled != enabled) {
        m_motionDetectionEnabled = enabled;
        emit motionDetectionEnabledChanged(m_motionDetectionEnabled);
    }
}

int SecurityCamera::motionSensitivity() const
{
    return m_motionSensitivity;
}

void SecurityCamera::setMotionSensitivity(int sensitivity)
{
    const int clamped = qBound(minSensitivity, sensitivity, maxSensitivity);
    if (m_motionSensitivity != clamped) {
        m_motionSensitivity = clamped;
        emit motionSensitivityChanged(m_motionSensitivity);
    }
}

void SecurityCamera::startStream()
{
    if (getDeviceState() == DeviceEnums::Off || m_isStreaming) return;

    m_isStreaming = true;
    emit isStreamingChanged(m_isStreaming);
}

void SecurityCamera::stopStream()
{
    if (!m_isStreaming) return;

    m_isStreaming = false;
    emit isStreamingChanged(m_isStreaming);
}

void SecurityCamera::startRecording()
{
    if (getDeviceState() == DeviceEnums::Off || m_isRecording) return;

    m_isRecording = true;
    emit isRecordingChanged(m_isRecording);
}

void SecurityCamera::stopRecording()
{
    if (!m_isRecording) return;

    m_isRecording = false;
    emit isRecordingChanged(m_isRecording);
}

void SecurityCamera::pan(int degrees)
{
    Q_UNUSED(degrees)
    // Hardware integration hook for pan position
}

void SecurityCamera::tilt(int degrees)
{
    Q_UNUSED(degrees)
    // Hardware integration hook for tilt position
}

void SecurityCamera::zoomIn()
{
    // Hardware integration hook for zoom
}

void SecurityCamera::zoomOut()
{
    // Hardware integration hook for zoom
}

void SecurityCamera::togglePower()
{
    auto newState = (getDeviceState() == DeviceEnums::On) 
                    ? DeviceEnums::Off 
                    : DeviceEnums::On;

    if (newState == DeviceEnums::Off) {
        stopStream();
        stopRecording();
    }

    setDeviceState(newState);
}