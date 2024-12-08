#include <ranges>
#include <numeric>

#include "Day1.h"
#include "utils/misc.h"

CDay1::CDay1(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 1: Historian Hysteria" } {}

void CDay1::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input1-1.txt");
    if (!lInput.has_value())
    {
        return;
    }

    std::vector<int> lLeftNumbers;
    std::vector<int> lRightNumbers;

    for (const auto lStr : lInput.value() | std::ranges::views::split(NEWLINE_DELIMITER))
    {
        const std::string_view lStrView{ lStr };
        const auto lNumbers = getNumbersFromString(lStrView);
        if (lNumbers.size() != 2)
        {
            std::cerr << "[ERROR] [SOLVE] Could not parse 2 numbers from string: " << lStrView << std::endl;
            return;
        }

        lLeftNumbers.push_back(lNumbers[0]);
        lRightNumbers.push_back(lNumbers[1]);
    }

    std::ranges::sort(lLeftNumbers);
    std::ranges::sort(lRightNumbers);

    const auto lDeltas = std::ranges::views::zip(lLeftNumbers, lRightNumbers)
        | std::ranges::views::transform([](auto aPair) {
            const auto [lLeft, lRight] = aPair;
            return std::abs(lLeft - lRight);
        });
    const auto lSum  = std::accumulate(lDeltas.begin(), lDeltas.end(), 0);

    std::cout << "Task 1 Sum: " << lSum << std::endl;

    const int64_t lSimilarityScore = std::transform_reduce(
        lLeftNumbers.begin(), lLeftNumbers.end(),
        int64_t{ 0 },
        std::plus{},
        [&](const auto& aNum) {
            return std::ranges::count(lRightNumbers, aNum) * aNum;
        }
    );

    std::cout << "Task 2 Similarity Score: " << lSimilarityScore << std::endl;

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
