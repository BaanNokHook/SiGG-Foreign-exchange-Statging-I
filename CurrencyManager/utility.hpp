/**
 * @file utility.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>

#include <QDebug>

#include "exception.hpp"

using namespace std;

struct Purchase
{
    std::string date;
    std::string type;
    double      amount;
    double      price;
    double      sum;
    std::string bank_name;
    std::string account;
};

struct CurrencyExchangeData
{
    std::string currency_;
    std::string change_;
    std::string cost_;
};

struct BalanceData
{
    std::string date_;
    std::string balance_;
};

namespace Utility
{
    const string loadDocument(const string& file_name);
    bool saveDocument(const std::string& filename, const std::string& data);
    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left);

    //TODO ARGS
    void normalizeString(std::string& where, const std::string& what);
    std::string normalizeString(std::string where);

    const std::string getDateTime();

    std::vector<std::string> readSettings(const std::string& file);
    const std::string getHostFromUrl(const std::string& file);

    bool is_equal(double x, double y);
}

#endif // UTILITY_H
