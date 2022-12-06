/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "coincontroltreewidget.h"

#include "coincontroldialog.h"

CoinControlTreeWidget::CoinControlTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
}

void CoinControlTreeWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) // press spacebar -> select checkbox
    {
        event->ignore();
        int COLUMN_CHECKBOX = 0;
        if (this->currentItem())
            this->currentItem()->setCheckState(COLUMN_CHECKBOX, ((this->currentItem()->checkState(COLUMN_CHECKBOX) == Qt::Checked) ? Qt::Unchecked : Qt::Checked));
    } else if (event->key() == Qt::Key_Escape) // press esc -> close dialog
    {
        event->ignore();
        CoinControlDialog* coinControlDialog = (CoinControlDialog*)this->parentWidget();
        coinControlDialog->done(QDialog::Accepted);
    } else {
        this->QTreeWidget::keyPressEvent(event);
    }
}
