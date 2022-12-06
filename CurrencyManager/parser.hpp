/**
 * @file parser.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PARSER_H
#define PARSER_H

//#define NO_LOGS

#include <memory>
#include <fstream>
#include <vector>

#include <QDebug>

#include "gq/Document.h"
#include "gq/Node.h"
#include "gq/Selection.h"

#include "nlohmann/json.hpp"

#include "curl_handler.hpp"
#include "utility.hpp"

using json = nlohmann::json;

class Parser
{

public:
    explicit Parser();

    std::vector<CurrencyExchangeData> parseCurrencyExchangeRate() const;

private:
    std::vector<std::string> settings_;
    std::unique_ptr<CurlHandler> curl_handler_;
};

#endif // PARSER_H
