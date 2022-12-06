/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "dynamicaddressvalidator.h"

#include "base58.h"

/* Base58 characters are:
     "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"

  This is:
  - All numbers except for '0'
  - All upper-case letters except for 'I' and 'O'
  - All lower-case letters except for 'l'
*/

DynamicAddressEntryValidator::DynamicAddressEntryValidator(QObject* parent) : QValidator(parent)
{
}

QValidator::State DynamicAddressEntryValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos);

    // Empty address is "intermediate" input
    if (input.isEmpty())
        return QValidator::Intermediate;

    // Correction
    for (int idx = 0; idx < input.size();) {
        bool removeChar = false;
        QChar ch = input.at(idx);
        // Corrections made are very conservative on purpose, to avoid
        // users unexpectedly getting away with typos that would normally
        // be detected, and thus sending to the wrong address.
        switch (ch.unicode()) {
        // Qt categorizes these as "Other_Format" not "Separator_Space"
        case 0x200B: // ZERO WIDTH SPACE
        case 0xFEFF: // ZERO WIDTH NO-BREAK SPACE
            removeChar = true;
            break;
        default:
            break;
        }

        // Remove whitespace
        if (ch.isSpace())
            removeChar = true;

        // To next character
        if (removeChar)
            input.remove(idx, 1);
        else
            ++idx;
    }

    // Validation
    QValidator::State state = QValidator::Acceptable;
    for (int idx = 0; idx < input.size(); ++idx) {
        int ch = input.at(idx).unicode();

        if (((ch >= '0' && ch <= '9') ||
                (ch >= 'a' && ch <= 'z') ||
                (ch >= 'A' && ch <= 'Z')) &&
            ch != 'l' && ch != 'I' && ch != '0' && ch != 'O') {
            // Alphanumeric and not a 'forbidden' character
        } else {
            state = QValidator::Invalid;
        }
    }

    return state;
}

DynamicAddressCheckValidator::DynamicAddressCheckValidator(QObject* parent) : QValidator(parent)
{
}

QValidator::State DynamicAddressCheckValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos);
    // Validate the passed Dynamic address
    const CTxDestination dest = DecodeDestination(input.toStdString());
    if (IsValidDestination(dest))
        return QValidator::Acceptable;

    return QValidator::Invalid;
}
