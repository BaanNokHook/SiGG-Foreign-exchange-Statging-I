/**
 * @file db_handler.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QDebug>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "utility.hpp"

enum class OperationType
{
    SELL,
    BUY
};

class DataBaseHandler
{

private:
    sql::Driver *driver_;
    sql::Connection *connection_;
    std::vector<std::string> settings_;

    void connectToDB();

public:
    DataBaseHandler();

    bool insertBuySellOperation(const Purchase& purchase);
    void insertCurrencyExchangeRateToDB();
    double getAccountBalance() const;
    double getCurrencyExchangeRate(const std::string& currency = "USDRUB");
    bool updateBankAccount(int amount) const;
    std::vector<Purchase> getActualPurchases() const;
    std::vector<BalanceData> getBalanceHistory() const;
};

#endif // DB_HANDLER_H
