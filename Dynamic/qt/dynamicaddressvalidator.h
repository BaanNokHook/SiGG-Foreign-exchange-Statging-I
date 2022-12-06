/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_DYNAMICADDRESSVALIDATOR_H
#define DYNAMIC_QT_DYNAMICADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DynamicAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DynamicAddressEntryValidator(QObject* parent);

    State validate(QString& input, int& pos) const;
};

/** Dynamic address widget validator, checks for a valid Dynamic address.
 */
class DynamicAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DynamicAddressCheckValidator(QObject* parent);

    State validate(QString& input, int& pos) const;
};

#endif // DYNAMIC_QT_DYNAMICADDRESSVALIDATOR_H
