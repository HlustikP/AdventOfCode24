#pragma once
#include <filesystem>
#include <fstream>
#include <optional>
#include <algorithm>

constexpr auto NEWLINE_DELIMITER = '\n';

constexpr auto ASCII_ZERO = 48;
constexpr auto ASCII_NINE = 57;

struct PodDimensions
{
    int mWidth;
    int mHeight;
};

std::optional<std::string> readFile(const std::filesystem::path& aPath);
bool charIsDigit(char aChar);
std::optional<int> charDigitToInt(char aChar);
bool charIsLetter(char aChar);
std::vector<int> getNumbersFromString(std::string_view aSv);
std::vector<int64_t> getNumbersFromStringInt64(std::string_view aSv);
PodDimensions getDimensionsFromString(const std::string& aString, char aLineEnding = NEWLINE_DELIMITER);
int64_t concatNumbers(int64_t aLhs, int64_t aRhs);


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

void clearConsole();
