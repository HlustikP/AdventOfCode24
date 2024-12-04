#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <algorithm>

namespace fs = std::filesystem;

constexpr auto NEWLINE_DELIMITER = '\n';

constexpr auto ASCII_ZERO = 48;
constexpr auto ASCII_NINE = 57;

inline std::optional<std::string> readFile(const fs::path& aPath)
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

inline bool charIsDigit(const char aChar)
{
    return aChar <= '9' && aChar >= '0';
}

inline std::optional<int> charDigitToInt(const char aChar)
{
    if (!charIsDigit(aChar)) {
        return std::nullopt;
    }

    return aChar - ASCII_ZERO;
}

inline bool charIsLetter(const char aChar)
{
    return (aChar <= 'z' && aChar >= 'a') || (aChar <= 'Z' && aChar >= 'A');
}

template <typename T>
bool itrIsFirstLine(T aItrBegin, T aItrCurrent, int aLineSize)
{
    return std::distance(aItrBegin, aItrCurrent) < aLineSize;
}

template <typename T>
bool itrIsLastLine(T aItrBegin, T aItrCurrent, int aLineSize, int aLineCount)
{
    return std::distance(aItrBegin, aItrCurrent) >= aLineSize * (aLineCount - 1);
}

template <typename T>
bool itrIsFirstColumn(T aItrBegin, T aItrCurrent, int aLineSize)
{
    return std::distance(aItrBegin, aItrCurrent) % aLineSize == 0;
}

template <typename T>
bool itrIsLastColumn(T aItrBegin, T aItrCurrent, int aLineSize)
{
    return std::distance(aItrBegin, aItrCurrent) % aLineSize == aLineSize - 1;
}

template <typename T>
std::ostream& operator<<(std::ostream& aOs, const std::vector<T>& aVec)
{
    for (const auto& lV : aVec) {
        aOs << lV << " ";
    }

    return aOs;
}

template <typename T>
std::optional<T> operator*= (std::optional<T>& aLhs, const T& aRhs)
{
    if (!aLhs.has_value()) {
        return std::nullopt;
    }

    aLhs = aLhs.value() * aRhs;
    return aLhs;
}

template <typename T>
std::optional<T> operator+= (std::optional<T>& aLhs, const T& aRhs)
{
    if (!aLhs.has_value()) {
        return std::nullopt;
    }

    aLhs = aLhs.value() + aRhs;
    return aLhs;
}

inline std::vector<int> getNumbersFromString(std::string_view aSv)
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

template <typename T, size_t N>
std::vector<T> getNumbersFromString(std::string_view aSv, const std::array<char, N> aSkipChars)
{
    std::vector<T> lNumbers;
    T lCurrentNumber = -1;
    T lCurrentDigit = 0;
    auto lItr = aSv.end() - 1;

    while (lItr >= aSv.begin()) {
        if (std::find(aSkipChars.begin(), aSkipChars.end(), *lItr) != aSkipChars.end()) {
            --lItr;
            continue;
        }

        if (*lItr == '-') {
            lCurrentNumber *= -1;
            --lItr;
            continue;
        }

        if (!charIsDigit(*lItr)) {
            if (lCurrentNumber > -1) {
                lNumbers.push_back(lCurrentNumber);
                lCurrentDigit = 0;
                lCurrentNumber = -1;
            }
        }
        else {
            if (const auto lDigit = charDigitToInt(*lItr); lDigit.has_value()) {
                if (lCurrentNumber == -1) {
                    lCurrentNumber = 0;
                }

                lCurrentNumber += lDigit.value() * static_cast<T>(std::pow(10, lCurrentDigit));
                ++lCurrentDigit;
            }
        }

        if (lItr == aSv.begin()) [[unlikely]] {
            break;
            }
        --lItr;
    }

    if (lCurrentNumber > -1) {
        lNumbers.push_back(lCurrentNumber);
    }

    return lNumbers;
};

struct PodDimensions
{
    int mWidth;
    int mHeight;
};

inline PodDimensions getDimensionsFromString(const std::string& aString, char aLineEnding = NEWLINE_DELIMITER)
{
    PodDimensions lDimensions{ .mWidth= 0, .mHeight= 0 };

    const auto lDelimiterCount = static_cast<int>(std::ranges::count(aString, aLineEnding));
    lDimensions.mHeight = aString.back() == aLineEnding ? lDelimiterCount : lDelimiterCount + 1;
    lDimensions.mWidth = static_cast<int>(std::distance(aString.begin(), std::ranges::find(aString, aLineEnding)));

    return lDimensions;
}
