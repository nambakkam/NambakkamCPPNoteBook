#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QJsonObject>
#include <QJsonDocument>

class MqttService : public QObject {
    Q_OBJECT

public:
    explicit MqttService(QObject *parent = nullptr);
    void connectToBroker(const QString &host = "127.0.0.1", quint16 port = 1883);

public slots:
    void publishDeviceState(const QString &deviceId, const QJsonObject &state);

signals:
    void deviceStateReceived(const QString &deviceId, const QJsonObject &state);
    void connected();

private slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    QMqttClient *m_client{nullptr};
};

#endif // MQTTSERVICE_H