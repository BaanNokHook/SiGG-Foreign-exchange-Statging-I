/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_COINCONTROLTREEDIALOG_H
#define DYNAMIC_QT_COINCONTROLTREEDIALOG_H

#include <QKeyEvent>
#include <QTreeWidget>

class CoinControlTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit CoinControlTreeWidget(QWidget* parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
};

#endif // DYNAMIC_QT_COINCONTROLTREEDIALOG_H
