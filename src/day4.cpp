#include <ranges>
#include <array>
#include <string>
#include <numeric>

#include "Day4.h"
#include "utils.hpp"

CDay4::CDay4(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 4: Ceres Search" } {}

auto constexpr XMAS_STRING = "XMAS";
auto constexpr STRIDE_MOVE_RIGHT = 1;

void CDay4::solve()
{
    printHeadline();

    auto lInput = loadFile("input4-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mStart = std::chrono::high_resolution_clock::now();

    const auto [lWidth, lHeight] = getDimensionsFromString(lText);
    auto lXmasCount = 0;
    auto lMasCrossCount = 0;

    const auto lStrideMoveDown = lWidth + 1;
    const auto lStrideMoveDownRight = lWidth + 2;
    const auto lStrideMoveDownLeft = lWidth;

    const std::array lStrides {
        STRIDE_MOVE_RIGHT,
        lStrideMoveDown,
        lStrideMoveDownRight,
        lStrideMoveDownLeft
    };

    const std::array lStridesPart2 {
        lStrideMoveDownRight,
        lStrideMoveDownLeft
    };

    auto lXCharView = lText
        | std::ranges::views::enumerate
        | std::ranges::views::filter([](auto aElement) {
        const auto [lIndex, lChar] = aElement;
        return lChar == 'X';
            });

    auto lReverseXCharView = lText
        | std::ranges::views::reverse
        | std::ranges::views::enumerate
        | std::ranges::views::filter([](auto aElement) {
        const auto [lIndex, lChar] = aElement;
        return lChar == 'X';
            });

    for (auto lXCharItr : lXCharView)
    {
        for (const auto lStride : lStrides)
        {
            auto lXmasView = lText
                | std::ranges::views::drop(std::get<0>(lXCharItr))
                | std::ranges::views::stride(lStride)
                | std::ranges::views::take(strlen(XMAS_STRING));

            const std::string lXmasString{lXmasView.begin(), lXmasView.end()};
            if (lXmasString == XMAS_STRING)
            {
                ++lXmasCount;
            }
        }
    }

    for (auto lXCharItr : lReverseXCharView)
    {
        for (const auto lStride : lStrides)
        {
            auto lXmasView = lText
                | std::ranges::views::reverse
                | std::ranges::views::drop(std::get<0>(lXCharItr))
                | std::ranges::views::stride(lStride)
                | std::ranges::views::take(strlen(XMAS_STRING));

            const std::string lXmasString{lXmasView.begin(), lXmasView.end()};
            if (lXmasString == XMAS_STRING)
            {
                ++lXmasCount;
            }
        }
    }

    // Part 2
    auto lACharView = lText
        | std::ranges::views::enumerate
        | std::ranges::views::filter([](auto aElement) {
        const auto [lIndex, lChar] = aElement;
        return lChar == 'A';
            });

    auto lReverseACharView = lText
        | std::ranges::views::reverse
        | std::ranges::views::enumerate
        | std::ranges::views::filter([](auto aElement) {
        const auto [lIndex, lChar] = aElement;
        return lChar == 'A';
            });

    auto lXCharReverseItr = lReverseACharView.begin();
    for (auto lXCharItr = lACharView.begin(); lXCharItr != lACharView.end(); ++lXCharItr, ++lXCharReverseItr)
    {
        std::string lString{};

        for (const auto lStride : lStridesPart2)
        {
            auto lXmasView = lText
                | std::ranges::views::drop(std::get<0>(*lXCharItr))
                | std::ranges::views::stride(lStride)
                | std::ranges::views::take(2);

            if (std::ranges::distance(lXmasView) == 2)
            {
                lString += *(lXmasView.begin() + 1);
            }

            auto lXmasReverseView = lText
                | std::ranges::views::reverse
                | std::ranges::views::drop(lText.size() - std::get<0>(*lXCharItr) - 1)
                | std::ranges::views::stride(lStride)
                | std::ranges::views::take(2);

            if (std::ranges::distance(lXmasReverseView) == 2)
            {
                lString += *(lXmasReverseView.begin() + 1);
            }
        }

        // Ignore less than 4 characters and strings containing X or newlines
        if (lString.size() == 4 && !lString.contains('X') && !lString.contains(NEWLINE_DELIMITER))
        {
            // MAS cross has 2 M and 2 S
            if (std::ranges::count(lString, 'M') == 2 && std::ranges::count(lString, 'S') == 2)
            {
                // Ignore MAM-SAS cross
                if (lString[0] != lString[1])
                {
                    lMasCrossCount++;
                }
            }
        }
    }

    mEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - XMAS Count: " << lXmasCount << std::endl;
    std::cout << "Task 2 - MAS Cross Count: " << lMasCrossCount << std::endl;

    printTime();
}
