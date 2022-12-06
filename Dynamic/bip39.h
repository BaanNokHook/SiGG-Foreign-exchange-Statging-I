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
 * Copyright (c) 2013-2014 Tomas Dzetkulic
 * Copyright (c) 2013-2014 Pavol Rusnak
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef DYNAMIC_BIP39_H
#define DYNAMIC_BIP39_H

#include "support/allocators/secure.h"

class CMnemonic
{
public:

    enum Language {
        ENGLISH = 0,
        CHINESE_SIMPLIFIED = 1,
        CHINESE_TRADITIONAL = 2,
        FRENCH = 3,
        GERMAN = 4,
        ITALIAN = 5,
        JAPANESE = 6,
        KOREAN = 7,
        RUSSIAN = 8,
        SPANISH = 9,
        UKRAINIAN = 10
    };

    static SecureString Generate(int strength, Language selectLanguage = Language::ENGLISH); // strength in bits
    static SecureString FromData(const SecureVector& data, int len, Language selectLanguage = Language::ENGLISH);
    static bool Check(SecureString mnemonic, Language selectLanguage = Language::ENGLISH);
    // passphrase must be at most 256 characters or code may crash
    static void ToSeed(SecureString mnemonic, SecureString passphrase, SecureVector& seedRet);
    static Language getLanguageEnumFromLabel(const std::string &input);

private:
    static void getWordList(const char* const* &input, Language selectLanguage = Language::ENGLISH);
  

};

#endif
