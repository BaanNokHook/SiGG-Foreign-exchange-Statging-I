/**
 * @file balancedataobject.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "balancedataobject.hpp"

BalanceDataObject::BalanceDataObject(const BalanceData& data) :
    date_(QString::fromStdString(data.date_)), balance_(QString::fromStdString(data.balance_))
{

}

QString BalanceDataObject::date() const
{
    return this->date_;
}

QString BalanceDataObject::balance() const
{
    return this->balance_;
}
