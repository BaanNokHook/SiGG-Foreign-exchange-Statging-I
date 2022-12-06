/**
 * @file balancedataobject.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BALANCEDATAOBJECT_HPP
#define BALANCEDATAOBJECT_HPP

#include "utility.hpp"

class BalanceDataObject
{
public:
    BalanceDataObject(const BalanceData& data);

    QString date() const;
    QString balance() const;

private:
    QString date_;
    QString balance_;
};

#endif // BALANCEDATAOBJECT_HPP
