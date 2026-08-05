#include "thememanager.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
ThemeManager::ThemeManager(QObject *parent)
    : QObject{parent}
{
    loadTheme(DeviceEnums::DARK);
}

void ThemeManager::loadTheme(DeviceEnums::Themes theme)
{
    QString themeFileName;
    switch (theme) {
    case DeviceEnums::DARK:
        themeFileName = ":/view/assets/themes/dark.json";
        break;
    case DeviceEnums::ECO:
        themeFileName = ":/view/assets/themes/eco.json";
        break;
    case DeviceEnums::BRIGHT:
        themeFileName = ":/view/assets/themes/light.json";
        break;
    case DeviceEnums::NAVY:
        themeFileName = ":/view/assets/themes/navy.json";
        break;
    case DeviceEnums::SAND:
        themeFileName = ":/view/assets/themes/sand.json";
        break;
    }
    QFile themeFile(themeFileName);
    if (!themeFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open theme file:" << themeFileName;
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(themeFile.readAll());
    themeFile.close();

    if (!doc.isObject()) return;

    QJsonObject root = doc.object();
    m_colors = root["colors"].toObject().toVariantMap();
    m_fonts = root["fonts"].toObject().toVariantMap();
    m_currentTheme = root["themeName"].toString();
    qDebug() << "colors: " << m_colors << "m_fonts: " << m_fonts << "themeName: " << m_currentTheme;
    emit themeChanged();
}

QVariantMap ThemeManager::colors()
{
    return m_colors;
}

QVariantMap ThemeManager::fonts()
{
    return m_fonts;
}

QString ThemeManager::themeName()
{
    return m_currentTheme;
}

QVariantList ThemeManager::themesModel() const
{
    return QVariantList{
        QVariantMap{{"themeName", "Midnight Slate"},           {"themeEnum", DeviceEnums::DARK}},
        QVariantMap{{"themeName", "Eco Emerald"}, {"themeEnum", DeviceEnums::ECO}},
        QVariantMap{{"themeName", "Bright Day"}, {"themeEnum", DeviceEnums::BRIGHT}},
        QVariantMap{{"themeName", "Deep Navy"}, {"themeEnum", DeviceEnums::NAVY}},
        QVariantMap{{"themeName", "Warm Sand"}, {"themeEnum", DeviceEnums::SAND}},
    };
}
