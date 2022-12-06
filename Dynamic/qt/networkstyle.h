/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_NETWORKSTYLE_H
#define DYNAMIC_QT_NETWORKSTYLE_H

#include <QIcon>
#include <QPixmap>
#include <QString>

/* Coin network-specific GUI style information */
class NetworkStyle
{
public:
    /** Get style associated with provided BIP70 network id, or 0 if not known */
    static const NetworkStyle* instantiate(const QString& networkId);

    const QString& getAppName() const { return appName; }
    const QIcon& getAppIcon() const { return appIcon; }
    const QPixmap& getSplashImage() const { return splashImage; }
    const QIcon& getTrayAndWindowIcon() const { return trayAndWindowIcon; }
    const QString& getTitleAddText() const { return titleAddText; }

private:
    NetworkStyle(const QString& appName, const int iconColorHueShift, const int iconColorSaturationReduction, const char* titleAddText);

    QString appName;
    QIcon appIcon;
    QPixmap splashImage;
    QIcon trayAndWindowIcon;
    QString titleAddText;

    void rotateColors(QImage& img, const int iconColorHueShift, const int iconColorSaturationReduction);
};

#endif // DYNAMIC_QT_NETWORKSTYLE_H
