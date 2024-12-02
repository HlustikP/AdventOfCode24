#include <ranges>
#include <numeric>

#include "Day2.h"
#include "utils.hpp"

CDay2::CDay2(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 2: Red-Nosed Reports" } {}

enum class EReportState
{
    Increasing,
    Decreasing
};

void CDay2::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input2-1.txt");
    if (!lInput.has_value())
    {
        return;
    }

    int lSafeReportsTask1 = 0;
    int lSafeReportsTask2 = 0;
    for (const auto lStr : lInput.value() | std::ranges::views::split(NEWLINE_DELIMITER))
    {
        const std::string_view lStrView{ lStr };
        const auto lNumbers = getNumbersFromString(lStrView);

        std::optional<EReportState> lState{std::nullopt};
        auto lChunks = lNumbers | std::ranges::views::chunk_by([&lState](auto aLhs, auto aRhs) {
                    if (aLhs == aRhs || std::abs(aLhs - aRhs) > 3)
                    {
                        return true;
                    }
                    if (aLhs < aRhs)
                    {
                        if (lState == EReportState::Decreasing)
                        {
                            lState = EReportState::Increasing;
                            return true;
                        }
                        lState = EReportState::Increasing;
                    }
                    else
                    {
                        if (lState == EReportState::Increasing)
                        {
                            lState = EReportState::Decreasing;
                            return true;
                        }
                        lState = EReportState::Decreasing;
                    }
                    return false;
                });

        // If the number of chunks is equal to the total number of numbers, then the report is safe
        if (std::ranges::distance(lChunks) == lNumbers.size())
        {
            lSafeReportsTask1++;
        }

        for (auto lNumIndex = 0; lNumIndex < lNumbers.size(); lNumIndex++)
        {
            lState = std::nullopt;
            auto lTask2Chunks = lNumbers
                // Create tuples of index and value
                | std::ranges::views::enumerate
                // Filter out the nth element
                | std::ranges::views::filter([lNumIndex](auto aElement) {
                const auto [lIndex, lValue] = aElement;
                return lIndex != lNumIndex;
                    })
                // Create chunks that dont satisfy the condition (chunking is done when predicate returns true)
                | std::ranges::views::chunk_by([&lState](auto aLhs, auto aRhs) {
                    const auto [lLeftIndex, lLhs] = aLhs;
                    const auto [lRightIndxe, lRhs] = aRhs;

                    if (lLhs == lRhs || std::abs(lLhs - lRhs) > 3)
                    {
                        return true;
                    }
                    if (lLhs < lRhs)
                    {
                        if (lState == EReportState::Decreasing)
                        {
                            lState = EReportState::Increasing;
                            return true;
                        }
                        lState = EReportState::Increasing;
                    }
                    else
                    {
                        if (lState == EReportState::Increasing)
                        {
                            lState = EReportState::Decreasing;
                            return true;
                        }
                        lState = EReportState::Decreasing;
                    }
                    return false;
                });

            // If the number of chunks is equal to the total number of numbers - 1 (because we remove one),
            // then the report is safe
            if (std::ranges::distance(lTask2Chunks) == lNumbers.size() - 1)
            {
                lSafeReportsTask2++;
                break;
            }
        }
    }

    std::cout << "Task 1 Safe Reports: " << lSafeReportsTask1 << std::endl;
    std::cout << "Task 2 Safe Reports: " << lSafeReportsTask2 << std::endl;

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
