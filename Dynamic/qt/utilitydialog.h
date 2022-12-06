/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_UTILITYDIALOG_H
#define DYNAMIC_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class ClientModel;
class DynamicGUI;

namespace Ui
{
class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    enum HelpMode {
        about,
        cmdline,
        pshelp
    };

    explicit HelpMessageDialog(QWidget* parent, HelpMode helpMode);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog* ui;
    QString text;

private Q_SLOTS:
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    ShutdownWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
    static QWidget* showShutdownWindow(DynamicGUI* window);

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // DYNAMIC_QT_UTILITYDIALOG_H
