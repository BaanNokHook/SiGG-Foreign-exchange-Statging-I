/**
 * @file currexcdata_object.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CURREXCDATAOBJECT_HPP
#define CURREXCDATAOBJECT_HPP

#include "utility.hpp"

class CurrExcDataObject
{
public:
    CurrExcDataObject(const CurrencyExchangeData &currencyExchangeData);

    QString currency() const;
    QString change() const;
    QString cost() const;

private:

    QString currency_;
    QString change_;
    QString cost_;
};

#endif // CURREXCDATAOBJECT_HPP
