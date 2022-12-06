/**
 * @file parser.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "parser.hpp"

Parser::Parser() :curl_handler_(nullptr)
{
    curl_handler_ = std::make_unique<CurlHandler>();

    curl_handler_->setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) 	Chrome/91.0.4472.124 Safari/537.36");
    curl_handler_->setHeader("Connection", "Keep-Alive");
    curl_handler_->setHeader("Accept-Language", "en-US,en;q=0.9");

    settings_ = Utility::readSettings("parser_settings.txt");

}

std::vector<CurrencyExchangeData> Parser::parseCurrencyExchangeRate() const
{
    const std::string url{settings_.at(2)};
    vector<CurrencyExchangeData> data{};

    curl_handler_->setHeader("Host", Utility::getHostFromUrl(url));
    curl_handler_->setHeader("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0");

    curl_handler_->query(url, methodType::GET);

    string table_name = Utility::parseDataFromPage(curl_handler_->getResponse(),
                                                    "Table__table_", " Table__", true);
    CDocument html{};
    html.parse(curl_handler_->getResponse());

    CSelection select = html.find('.' + table_name);

    if(!select.nodeNum())
    {
        qDebug()<<"No results in parseCurrencyExchangeRate()";
        return data;
    }

    int num = select.nodeAt(0).childAt(1).childNum();

    data.reserve(num);

    for(int i = 0; i< num; ++ i)
    {
        CurrencyExchangeData temp;

        temp.currency_ = select.nodeAt(0).childAt(1).childAt(i).childAt(0).text().c_str();
        temp.change_ = select.nodeAt(0).childAt(1).childAt(i).childAt(1).text().c_str();
        temp.cost_ = select.nodeAt(0).childAt(1).childAt(i).childAt(2).text().c_str();

        data.push_back(temp);
    }

    return data;
}












