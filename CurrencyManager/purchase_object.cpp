/**
 * @file purchase_object.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "purchase_object.hpp"

PurchaseObject::PurchaseObject(const Purchase &purchase) :
    date_(QString::fromStdString(purchase.date)), ptype_(QString::fromStdString(purchase.type)),
    amount_(purchase.amount), price_(purchase.price), sum_(purchase.sum),
    bank_name_(QString::fromStdString(purchase.bank_name)),
    account_(QString::fromStdString(purchase.account))
{

}

QString PurchaseObject::date() const
{
    return date_;
}

QString PurchaseObject::ptype() const
{
    return ptype_;
}

double PurchaseObject::amount() const
{
    return amount_;
}

double PurchaseObject::price() const
{
    return price_;
}

double PurchaseObject::sum() const
{
    return sum_;
}

QString PurchaseObject::bank_name() const
{
    return bank_name_;
}

QString PurchaseObject::account() const
{
    return account_;
}
