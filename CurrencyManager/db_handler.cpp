/**
 * @file db_handler.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "db_handler.hpp"

DataBaseHandler::DataBaseHandler(): driver_(nullptr),
    connection_(nullptr)
{
    settings_ = Utility::readSettings("db_settings.txt");

    connectToDB();
}

void DataBaseHandler::connectToDB()
{
    driver_ = get_driver_instance();
    connection_ = driver_->connect(settings_.at(0), settings_.at(1), settings_.at(2));
    connection_->setSchema(settings_.at(3));
}

double DataBaseHandler::getAccountBalance() const
{
    std::unique_ptr<sql::Statement> stmt{connection_->createStatement()};

    unique_ptr<sql::ResultSet> res {
        stmt->executeQuery("SELECT balance FROM account_balance WHERE id = "
        "(SELECT MAX(id) FROM account_balance);") };

    res->next();

    return res->getDouble("balance");
}

double DataBaseHandler::getCurrencyExchangeRate(const string &currency)
{
    std::unique_ptr<sql::PreparedStatement> pstmt{ connection_->prepareStatement(
    "SELECT price FROM currencies WHERE type = ?;") };

    pstmt->setString(1, currency);
    unique_ptr<sql::ResultSet> res { pstmt->executeQuery() };
    res->next();
    return res->getDouble(1);
}

bool DataBaseHandler::updateBankAccount(int sum) const
{
    std::unique_ptr<sql::Statement> stmt{ connection_->createStatement()};

    unique_ptr<sql::ResultSet> res {
        stmt->executeQuery("SELECT balance FROM account_balance WHERE id = "
                            "(SELECT MAX(id) FROM account_balance);") };
    res->next();

    std::unique_ptr<sql::PreparedStatement> pstmt{ connection_->prepareStatement(
    "INSERT INTO account_balance (date, balance) VALUES (?,?);")};

    pstmt->setString(1, Utility::getDateTime());
    pstmt->setInt(2, sum + res->getInt(1));
    pstmt->executeUpdate();

    return true;
}

std::vector<Purchase> DataBaseHandler::getActualPurchases() const
{
    std::vector<Purchase> purchases;

    std::unique_ptr<sql::PreparedStatement> pstmt{ connection_->prepareStatement(
    "SELECT date, type, amount, price, sum, bank_name, account FROM my_purchases") };

    unique_ptr<sql::ResultSet> res { pstmt->executeQuery() };

    while (res->next())
    {
        Purchase purchase;

        purchase.date = res->getString(1);
        purchase.type = res->getString(2);
        purchase.amount = res->getDouble(3);
        purchase.price = res->getDouble(4);
        purchase.sum = res->getDouble(5);
        purchase.bank_name = res->getString(6);
        purchase.account = res->getString(7);

        purchases.push_back(purchase);
    }

    return purchases;
}

std::vector<BalanceData> DataBaseHandler::getBalanceHistory() const
{
    std::unique_ptr<sql::Statement> stmt{connection_->createStatement()};

    unique_ptr<sql::ResultSet> res {
        stmt->executeQuery("SELECT * FROM account_balance ORDER BY id DESC;")};

    std::vector<BalanceData> bdata;

    while (res->next())
    {
        BalanceData data;

        data.date_ = res->getString(2);
        data.balance_ = std::to_string(res->getDouble(3));

        bdata.push_back(data);
    }

    return bdata;
}

bool DataBaseHandler::insertBuySellOperation(const Purchase& purchase)
{
    std::unique_ptr<sql::PreparedStatement> pstmt{ connection_->prepareStatement(
    "INSERT INTO my_purchases (date, type, amount, price, sum, bank_name, account) "
        "VALUES (?,?,?,?,?,?,?);") };

    pstmt->setString(1, purchase.date);
    pstmt->setString(2, purchase.type);
    pstmt->setDouble(3, purchase.amount);
    pstmt->setDouble(4, purchase.price);
    pstmt->setDouble(5, purchase.sum);
    pstmt->setString(6, purchase.bank_name);
    pstmt->setString(7, purchase.account);

    pstmt->executeUpdate();

    return true;
}





