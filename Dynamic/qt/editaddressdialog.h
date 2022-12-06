/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_EDITADDRESSDIALOG_H
#define DYNAMIC_QT_EDITADDRESSDIALOG_H

#include <QDialog>

class AddressTableModel;

namespace Ui
{
class EditAddressDialog;
}

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

/** Dialog for editing an address and associated information.
 */
class EditAddressDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode {
        NewReceivingAddress,
        NewSendingAddress,
        EditReceivingAddress,
        EditSendingAddress
    };

    explicit EditAddressDialog(Mode mode, QWidget* parent);
    ~EditAddressDialog();

    void setModel(AddressTableModel* model);
    void loadRow(int row);

    QString getAddress() const;
    void setAddress(const QString& address);

public Q_SLOTS:
    void accept();

private:
    bool saveCurrentRow();

    Ui::EditAddressDialog* ui;
    QDataWidgetMapper* mapper;
    Mode mode;
    AddressTableModel* model;

    QString address;
};

#endif // DYNAMIC_QT_EDITADDRESSDIALOG_H
