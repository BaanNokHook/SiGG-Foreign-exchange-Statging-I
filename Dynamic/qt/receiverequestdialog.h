/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_RECEIVEREQUESTDIALOG_H
#define DYNAMIC_QT_RECEIVEREQUESTDIALOG_H

#include "walletmodel.h"

#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPainter>

class OptionsModel;

namespace Ui
{
class ReceiveRequestDialog;
}

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

/* Label widget for QR code. This image can be dragged, dropped, copied and saved
 * to disk.
 */
class QRImageWidget : public QLabel
{
    Q_OBJECT

public:
    explicit QRImageWidget(QWidget* parent = 0);
    QImage exportImage();

public Q_SLOTS:
    void saveImage();
    void copyImage();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void contextMenuEvent(QContextMenuEvent* event) override;

private:
    QMenu* contextMenu;
};

class ReceiveRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveRequestDialog(QWidget* parent = 0);
    ~ReceiveRequestDialog();

    void setModel(OptionsModel* model);
    void setInfo(const SendCoinsRecipient& info);

private Q_SLOTS:
    void on_btnCopyURI_clicked();
    void on_btnCopyAddress_clicked();

    void update();

private:
    Ui::ReceiveRequestDialog* ui;
    OptionsModel* model;
    SendCoinsRecipient info;
};

#endif // DYNAMIC_QT_RECEIVEREQUESTDIALOG_H
