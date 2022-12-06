/**
 * @file account_handler.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "account_handler.cpp"

AccountHandler::AccountHandler(QObject *parent) : QObject(parent),
    db_handler_(nullptr), parser_(nullptr)
{
    db_handler_ = std::make_unique<DataBaseHandler>();
    parser_ = std::make_unique<Parser>();
}

bool AccountHandler::buy(double amount)
{
    //TODO вывод не в консоль а в qml окно с ссобщением
    if(db_handler_->insertBuySellOperation(getPurchaseInstance(amount, "buy")))
    {
        updateBankAccountBalanceOnDB(amount);
        return true;
    }
    else
    {
        qDebug() << "Some error occured during bying";
        return false;
    }
}

bool AccountHandler::sell(double amount)
{
    //TODO вывод не в консоль а в qml окно с ссобщением

    if(Utility::is_equal(db_handler_->getAccountBalance(), 0.0f))
    {
        qDebug() << "Balance is zero, cannot sell";
        return false;
    }

    if(db_handler_->insertBuySellOperation(getPurchaseInstance(amount, "sell")))
    {
        updateBankAccountBalanceOnDB(amount*=-1);
        return true;
    }
    else
    {
        qDebug() << "Some error occured during selling";
        return false;
    }
}

bool AccountHandler::sellAll()
{
    double balance = getBankAccountBalanceFromDB();
    if(sell(balance))
    {
        return true;
    }
    else
    {
        qDebug() << "Some error occured during selling all";
        return false;
    }
}

double AccountHandler::getBankAccountBalanceFromDB()
{
    return db_handler_->getAccountBalance();
}

double AccountHandler::getExcangeRate() const
{
    return db_handler_->getCurrencyExchangeRate(selected_);
}

void AccountHandler::getSelectedCurrency(const QString type)
{
    selected_ = type.toStdString();
}

std::vector<CurrencyExchangeData> AccountHandler::getExcangeRates() const
{
    return parser_->parseCurrencyExchangeRate();
}

std::vector<Purchase> AccountHandler::getActiveLots() const
{
    return db_handler_->getActualPurchases();
}

std::vector<BalanceData> AccountHandler::getBalanceHistory() const
{
    return db_handler_->getBalanceHistory();
}

const Purchase AccountHandler::getPurchaseInstance(double amount, const std::string& type,
        const std::string bank, const std::string account) const
{
    Purchase purchase;
    purchase.date = Utility::getDateTime();
    purchase.type = type;
    purchase.amount = amount;
    purchase.price = this->getExcangeRate();
    purchase.sum = (amount * purchase.price);
    purchase.bank_name = bank;
    purchase.account = account;

    return purchase;
}

bool AccountHandler::updateBankAccountBalanceOnDB(int sum) const
{
    return db_handler_->updateBankAccount(sum);
}
