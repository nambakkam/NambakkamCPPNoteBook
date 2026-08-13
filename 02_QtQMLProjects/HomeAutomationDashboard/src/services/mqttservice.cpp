#include "mqttservice.h"
#include <QDebug>

MqttService::MqttService(QObject *parent) : QObject(parent) {
    m_client = new QMqttClient(this);

    connect(m_client, &QMqttClient::connected, this, [this]() {
        qDebug() << "[MQTT] Connected to broker successfully!";
        emit connected();
        
        // Subscribe to all light state updates
        m_client->subscribe(QMqttTopicFilter("home/light/+/state"));
    });

    connect(m_client, &QMqttClient::messageReceived, this, &MqttService::onMessageReceived);
}

void MqttService::connectToBroker(const QString &host, quint16 port) {
    m_client->setHostname(host);
    m_client->setPort(port);
    m_client->connectToHost();
}

void MqttService::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic) {
    // Expected Topic: home/light/<device_id>/state
    qDebug()<<"Message Received: "<<message;
    QStringList parts = topic.name().split('/');
    if (parts.size() < 4) return;

    QString deviceId = parts[2]; // Extracts "<device_id>"

    QJsonDocument doc = QJsonDocument::fromJson(message);
    if (!doc.isObject()) return;

    emit deviceStateReceived(deviceId, doc.object());
}

void MqttService::publishDeviceState(const QString &deviceId, const QJsonObject &state) {
    if (m_client->state() != QMqttClient::Connected) return;

    // Outbound Topic: home/light/<device_id>/set
    QString topic = QString("home/light/%1/set").arg(deviceId);
    QByteArray payload = QJsonDocument(state).toJson(QJsonDocument::Compact);

    m_client->publish(QMqttTopicName(topic), payload, 1 /* QoS 1 */);
}
