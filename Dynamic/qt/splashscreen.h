/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_SPLASHSCREEN_H
#define DYNAMIC_QT_SPLASHSCREEN_H

#include <QSplashScreen>
#include <functional>

class CWallet;
class NetworkStyle;

/** Class for the splashscreen with information of the running client.
 *
 * @note this is intentionally not a QSplashScreen. Dynamic initialization
 * can take a long time, and in that case a progress window that cannot be
 * moved around and minimized has turned out to be frustrating to the user.
 */
class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplashScreen(Qt::WindowFlags f, const NetworkStyle* networkStyle);
    ~SplashScreen();

protected:
    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent* event);

public Q_SLOTS:
    /** Slot to call finish() method as it's not defined as slot */
    void slotFinish(QWidget* mainWin);

    /** Show message and progress */
    void showMessage(const QString& message, int alignment, const QColor& color);

    /** Sets the break action */
    void setBreakAction(const std::function<void(void)>& action);

protected:
    bool eventFilter(QObject* obj, QEvent* ev);

private:
    /** Connect core signals to splash screen */
    void subscribeToCoreSignals();
    /** Disconnect core signals to splash screen */
    void unsubscribeFromCoreSignals();
    /** Connect wallet signals to splash screen */
    void ConnectWallet(CWallet*);

    QPixmap pixmap;
    QString curMessage;
    QColor curColor;
    int curAlignment;

    QList<CWallet*> connectedWallets;

    std::function<void(void)> breakAction;
};

#endif // DYNAMIC_QT_SPLASHSCREEN_H
