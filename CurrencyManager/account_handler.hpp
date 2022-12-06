/**
 * @file account_handler.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ACCOUNTHANDLER_HPP
#define ACCOUNTHANDLER_HPP

#include <memory>
#include <iomanip>

#include <QObject>
#include <QDebug>

#include "db_handler.hpp"
#include "parser.hpp"
#include "utility.hpp"

class AccountHandler : public QObject
{
    Q_OBJECT

public:
    explicit AccountHandler(QObject *parent = nullptr);

    Q_INVOKABLE bool buy(double amount);
    Q_INVOKABLE bool sell(double amount);
    Q_INVOKABLE bool sellAll();

    Q_INVOKABLE double getBankAccountBalanceFromDB();
    Q_INVOKABLE double getExcangeRate() const;
    Q_INVOKABLE void getSelectedCurrency(const QString type);

    std::vector<CurrencyExchangeData> getExcangeRates() const;
    std::vector<Purchase> getActiveLots() const;
    std::vector<BalanceData> getBalanceHistory() const;

private:
    std::unique_ptr<DataBaseHandler> db_handler_;
    std::unique_ptr<Parser> parser_;
    std::string selected_;

    const Purchase getPurchaseInstance(double amount, const std::string& type,
        const std::string bank = "Some bank", const std::string account = "1234567890") const;
    bool updateBankAccountBalanceOnDB(int sum) const;
};

#endif // ACCOUNTHANDLER_HPP
