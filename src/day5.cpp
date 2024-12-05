#include <ranges>

#include "Day5.h"
#include "utils.hpp"

CDay5::CDay5(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 5: Print Queue" } {}

struct PodOrderingRule
{
    int mLower;
    int mUpper;
};

static bool isInValidOrder(const std::vector<PodOrderingRule>& aOrderungRules, const std::vector<int>& aNumbers)
{
    for (const auto [lLowerRule, lUpperRule] : aOrderungRules)
    {
        const auto lLower = std::ranges::find(aNumbers, lLowerRule);
        const auto lUpper = std::ranges::find(aNumbers, lUpperRule);

        if (lLower == aNumbers.end() || lUpper == aNumbers.end())
        {
            continue;
        }

        if (lLower > lUpper)
        {
            return false;
        }
    }

    return true;
}

void CDay5::solve()
{
    printHeadline();

    const auto lInput = loadFile("input5-1.txt");
    if (!lInput.has_value())
    {
        return;
    }

    mStart = std::chrono::high_resolution_clock::now();

    const std::string& lText = lInput.value();
    std::vector<PodOrderingRule> lOrderungRules;
    int64_t lSumOfMiddleNums = 0;
    int64_t lSumOfMiddleNumsTask2 = 0;

    // Fill rules
    for (const auto lStr : lText | std::ranges::views::split(NEWLINE_DELIMITER))
    {
        const std::string_view lStrView{ lStr };
        const auto lNumbers = getNumbersFromString(lStrView);
        if (lNumbers.size() == 2)
        {
            lOrderungRules.push_back({ .mLower = lNumbers[1], .mUpper = lNumbers[0] });
        }
    }

    auto lPagesView = lText
        | std::ranges::views::split(NEWLINE_DELIMITER)
        | std::ranges::views::filter([](auto aView) {
            return !std::ranges::contains(aView, '|');
            })
        | std::ranges::views::transform([](auto aView) {
            return getNumbersFromString(std::string_view{ aView });
            })
        | std::ranges::views::filter([](const auto& aNumbers) {
            return !aNumbers.empty();
        });

    for (auto lNumbers : lPagesView)
    {
        std::ranges::reverse(lNumbers);

        if (isInValidOrder(lOrderungRules, lNumbers))
        {
            lSumOfMiddleNums += lNumbers[lNumbers.size() / 2];
        }
    }

    for (auto lNumbers : lPagesView)
    {
        if (lNumbers.empty())
        {
            continue;
        }

        std::ranges::reverse(lNumbers);
        if (isInValidOrder(lOrderungRules, lNumbers))
        {
            continue;
        }

        bool lIsSorted = false;
        while (!lIsSorted)
        {
            for (const auto lRule : lOrderungRules)
            {
                const auto lLower = std::ranges::find(lNumbers, lRule.mLower);
                const auto lUpper = std::ranges::find(lNumbers, lRule.mUpper);

                if (lLower == lNumbers.end() || lUpper == lNumbers.end())
                {
                    continue;
                }

                if (lLower < lUpper)
                {
                    continue;
                }

                std::swap(*lLower, *lUpper);
                if (isInValidOrder(lOrderungRules, lNumbers))
                {
                    lSumOfMiddleNumsTask2 += lNumbers[lNumbers.size() / 2];
                    lIsSorted = true;
                    break;
                }
            }
        }
    }

    mEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 Sum of Middle Nums: " << lSumOfMiddleNums << std::endl;
    std::cout << "Task 2 Sum of Middle Nums: " << lSumOfMiddleNumsTask2 << std::endl;

    printTime();
}
