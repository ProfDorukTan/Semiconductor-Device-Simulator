//
// Created by Doruk Tan Atila on 10/29/23.
// USING CHATGPT
//

#ifndef MAIN_CPP_STRING_TO_WIDECHAR_H
#define MAIN_CPP_STRING_TO_WIDECHAR_H

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <cstring>

wchar_t* stringToWideChar(const std::string& str);
void printWideString(const wchar_t* wideStr);

#endif //MAIN_CPP_STRING_TO_WIDECHAR_H
