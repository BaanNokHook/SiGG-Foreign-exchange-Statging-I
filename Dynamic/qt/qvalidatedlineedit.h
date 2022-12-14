/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_QVALIDATEDLINEEDIT_H
#define DYNAMIC_QT_QVALIDATEDLINEEDIT_H

#include <QLineEdit>

/** Line edit that can be marked as "invalid" to show input validation feedback. When marked as invalid,
   it will get a red background until it is focused.
 */
class QValidatedLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit QValidatedLineEdit(QWidget* parent);
    void clear();
    void setCheckValidator(const QValidator* v);
    bool isValid();

protected:
    void focusInEvent(QFocusEvent* evt);
    void focusOutEvent(QFocusEvent* evt);

private:
    bool valid;
    const QValidator* checkValidator;

public Q_SLOTS:
    void setValid(bool valid);
    void setEnabled(bool enabled);

Q_SIGNALS:
    void validationDidChange(QValidatedLineEdit* validatedLineEdit);

private Q_SLOTS:
    void markValid();
    void checkValidity();
};

#endif // DYNAMIC_QT_QVALIDATEDLINEEDIT_H
