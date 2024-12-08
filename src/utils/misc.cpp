#pragma once
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

#include "misc.h"

namespace fs = std::filesystem;

std::optional<std::string> readFile(const fs::path& aPath)
{
    if (!fs::exists(aPath)) {
        std::cerr << "[ERROR] [FILE] " << aPath << " does not exist" << std::endl;
        return std::nullopt;
    }

    try {
        std::ifstream lIfstream(aPath, std::ios::in | std::ios::binary);
        const auto lSize = fs::file_size(aPath);
        std::string lResult(lSize, '\0');
        lIfstream.read(lResult.data(), static_cast<std::streamsize>(lSize));

        return lResult;
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] [FILE] " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool charIsDigit(const char aChar)
{
    return aChar <= '9' && aChar >= '0';
}

std::optional<int> charDigitToInt(const char aChar)
{
    if (!charIsDigit(aChar)) {
        return std::nullopt;
    }

    return aChar - ASCII_ZERO;
}

bool charIsLetter(const char aChar)
{
    return (aChar <= 'z' && aChar >= 'a') || (aChar <= 'Z' && aChar >= 'A');
}

std::vector<int> getNumbersFromString(std::string_view aSv)
{
    std::vector<int> lNumbers;
    std::optional<int> lCurrentNumber = std::nullopt;
    int lCurrentDigit = 0;
    auto lItr = aSv.end() - 1;

    while (lItr >= aSv.begin()) {
        if (*lItr == '-') {
            lCurrentNumber *= -1;
            if (lItr == aSv.begin()) [[unlikely]] {
                break;
                }
            --lItr;
            continue;
        }

        if (!charIsDigit(*lItr)) {
            if (lCurrentNumber.has_value()) {
                lNumbers.push_back(lCurrentNumber.value());
                lCurrentDigit = 0;
                lCurrentNumber = std::nullopt;
            }
        }
        else {
            if (const auto lDigit = charDigitToInt(*lItr); lDigit.has_value()) {
                if (!lCurrentNumber.has_value()) {
                    lCurrentNumber = 0;
                }

                lCurrentNumber += lDigit.value() * static_cast<int>(std::pow(10, lCurrentDigit));
                lCurrentDigit++;
            }
        }

        if (lItr == aSv.begin()) [[unlikely]] {
            break;
        }
        --lItr;
    }

    if (lCurrentNumber.has_value()) {
        lNumbers.push_back(lCurrentNumber.value());
    }

    return lNumbers;
};

std::vector<int64_t> getNumbersFromStringInt64(std::string_view aSv)
{
    std::vector<int64_t> lNumbers;
    std::optional<int64_t> lCurrentNumber = std::nullopt;
    int64_t lCurrentDigit = 0;
    auto lItr = aSv.end() - 1;

    while (lItr >= aSv.begin()) {
        if (*lItr == '-') {
            lCurrentNumber *= -1ll;
            if (lItr == aSv.begin()) [[unlikely]] {
                break;
                }
            --lItr;
            continue;
        }

        if (!charIsDigit(*lItr)) {
            if (lCurrentNumber.has_value()) {
                lNumbers.push_back(lCurrentNumber.value());
                lCurrentDigit = 0;
                lCurrentNumber = std::nullopt;
            }
        }
        else {
            if (const auto lDigit = charDigitToInt(*lItr); lDigit.has_value()) {
                if (!lCurrentNumber.has_value()) {
                    lCurrentNumber = 0;
                }

                lCurrentNumber += lDigit.value() * static_cast<int64_t>(std::pow(10, lCurrentDigit));
                lCurrentDigit++;
            }
        }

        if (lItr == aSv.begin()) [[unlikely]] {
            break;
            }
        --lItr;
    }

    if (lCurrentNumber.has_value()) {
        lNumbers.push_back(lCurrentNumber.value());
    }

    return lNumbers;
};

PodDimensions getDimensionsFromString(const std::string& aString, char aLineEnding /* = NEWLINE_DELIMITER*/)
{
    PodDimensions lDimensions{ .mWidth= 0, .mHeight= 0 };

    const auto lDelimiterCount = static_cast<int>(std::ranges::count(aString, aLineEnding));
    lDimensions.mHeight = aString.back() == aLineEnding ? lDelimiterCount : lDelimiterCount + 1;
    lDimensions.mWidth = static_cast<int>(std::distance(aString.begin(), std::ranges::find(aString, aLineEnding)));

    return lDimensions;
}

int64_t concatNumbers(int64_t aLhs, int64_t aRhs) {
    const int64_t lNumDigits = static_cast<int64_t>(std::log10(aRhs)) + 1;
    return aLhs * static_cast<int64_t>(std::pow(10, lNumDigits)) + aRhs;
}

void clearConsole()
{
    const HANDLE lHConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    constexpr COORD lCoordScreen = { 0, 0 };
    DWORD lCCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO lCsbi;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(lHConsole, &lCsbi))
    {
        return;
    }

    const DWORD lDwConSize = lCsbi.dwSize.X * lCsbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(lHConsole,        // Handle to console screen buffer
        (TCHAR)' ',      // Character to write to the buffer
        lDwConSize,       // Number of cells to write
        lCoordScreen,     // Coordinates of first cell
        &lCCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(lHConsole, &lCsbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(lHConsole,         // Handle to console screen buffer
        lCsbi.wAttributes, // Character attributes to use
        lDwConSize,        // Number of cells to set attribute
        lCoordScreen,      // Coordinates of first cell
        &lCCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(lHConsole, lCoordScreen);
}
