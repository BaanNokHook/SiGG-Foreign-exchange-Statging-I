/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/**
 * Money parsing/formatting utilities.
 */
#ifndef DYNAMIC_UTILMONEYSTR_H
#define DYNAMIC_UTILMONEYSTR_H

#include "amount.h"

#include <stdint.h>
#include <string>

std::string FormatMoney(const CAmount& n);
bool ParseMoney(const std::string& str, CAmount& nRet);
bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // DYNAMIC_UTILMONEYSTR_H
