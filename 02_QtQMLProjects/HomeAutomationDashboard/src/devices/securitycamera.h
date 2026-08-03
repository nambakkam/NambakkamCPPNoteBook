#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "ismartdevice.h"

class SecurityCamera : public ISmartDevice
{
    Q_OBJECT

    // Video Feed & Recording Status
    Q_PROPERTY(bool isStreaming READ isStreaming NOTIFY isStreamingChanged)
    Q_PROPERTY(bool isRecording READ isRecording NOTIFY isRecordingChanged)

    // Feature Toggles
    Q_PROPERTY(bool nightVisionEnabled READ nightVisionEnabled WRITE setNightVisionEnabled NOTIFY nightVisionEnabledChanged)
    Q_PROPERTY(bool motionDetectionEnabled READ motionDetectionEnabled WRITE setMotionDetectionEnabled NOTIFY motionDetectionEnabledChanged)

    // Motion Settings
    Q_PROPERTY(int motionSensitivity READ motionSensitivity WRITE setMotionSensitivity NOTIFY motionSensitivityChanged)

    // Hardware Bounds
    Q_PROPERTY(int minSensitivity READ getMinSensitivity CONSTANT)
    Q_PROPERTY(int maxSensitivity READ getMaxSensitivity CONSTANT)

public:
    explicit SecurityCamera(const QString &name, QObject *parent = nullptr);

    bool isStreaming() const;
    bool isRecording() const;
    bool nightVisionEnabled() const;
    bool motionDetectionEnabled() const;
    int motionSensitivity() const;

    // Boundary getters
    static constexpr int minSensitivity{1};
    static constexpr int maxSensitivity{100};

    int getMinSensitivity() const { return minSensitivity; }
    int getMaxSensitivity() const { return maxSensitivity; }

public slots:
    void setNightVisionEnabled(bool enabled);
    void setMotionDetectionEnabled(bool enabled);
    void setMotionSensitivity(int sensitivity);

    // Operational Actions
    void startStream();
    void stopStream();
    void startRecording();
    void stopRecording();

    // PTZ (Pan-Tilt-Zoom) Actions
    void pan(int degrees);
    void tilt(int degrees);
    void zoomIn();
    void zoomOut();

    void togglePower() override;

signals:
    void isStreamingChanged(bool streaming);
    void isRecordingChanged(bool recording);
    void nightVisionEnabledChanged(bool enabled);
    void motionDetectionEnabledChanged(bool enabled);
    void motionSensitivityChanged(int sensitivity);
    void motionDetected();

private:
    bool m_isStreaming;
    bool m_isRecording;
    bool m_nightVisionEnabled;
    bool m_motionDetectionEnabled;
    int m_motionSensitivity;
};

#endif // SECURITYCAMERA_H