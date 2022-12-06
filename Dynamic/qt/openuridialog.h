/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_OPENURIDIALOG_H
#define DYNAMIC_QT_OPENURIDIALOG_H

#include <QDialog>

namespace Ui
{
class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(QWidget* parent);
    ~OpenURIDialog();

    QString getURI();

protected Q_SLOTS:
    void accept();

private:
    Ui::OpenURIDialog* ui;
};

#endif // DYNAMIC_QT_OPENURIDIALOG_H
