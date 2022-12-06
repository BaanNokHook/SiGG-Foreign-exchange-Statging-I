/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DYNAMIC_QT_BDAPFEESPOPUP_H
#define DYNAMIC_QT_BDAPFEESPOPUP_H

#include "bdap/fees.h"
#include "bdappage.h"
#include "dynamicunits.h"

#include <QDialog>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QTranslator>

bool bdapFeesPopup(QWidget *parentDialog, const opcodetype& opCodeAction, const opcodetype& opCodeObject, BDAP::ObjectType inputAccountType, int unit, int32_t regMonths = DEFAULT_REGISTRATION_MONTHS);

#endif // DYNAMIC_QT_BDAPFEESPOPUP_H