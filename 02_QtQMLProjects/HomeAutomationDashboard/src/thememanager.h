#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QVariantMap>
#include "deviceenums.h"
class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap colors READ colors NOTIFY themeChanged)
    Q_PROPERTY(QVariantMap fonts READ fonts NOTIFY themeChanged)
    Q_PROPERTY(QString themeName READ themeName NOTIFY themeChanged)
    Q_PROPERTY(QVariantList themesModel READ themesModel CONSTANT)
public:
    explicit ThemeManager(QObject *parent = nullptr);

    Q_INVOKABLE void loadTheme(DeviceEnums::Themes theme);
    QVariantMap colors();
    QVariantMap fonts();
    QString themeName();
    QVariantList themesModel() const;

private:
    QVariantMap m_colors;
    QVariantMap m_fonts;
    QString m_currentTheme;
signals:
    void themeChanged();
};

#endif // THEMEMANAGER_H
