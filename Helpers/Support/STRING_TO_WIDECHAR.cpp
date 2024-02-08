//
// Created by Doruk Tan Atila on 10/29/23.
// USING CHATGPT
//

#include "STRING_TO_WIDECHAR.h"

// Convert a std::string to a dynamically allocated wchar_t*
wchar_t* stringToWideChar(const std::string& str) {
    // Convert to std::wstring
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(str);

    // Create a wchar_t* and copy the contents
    wchar_t* wideStr = new wchar_t[wstr.length() + 1];
    wcscpy(wideStr, wstr.c_str());

    return wideStr;
}

// Print a wide character string
void printWideString(const wchar_t* wideStr) {
    std::wcout << wideStr << std::endl;
}
