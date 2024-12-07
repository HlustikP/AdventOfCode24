#include <ranges>
#include <numeric>

#include "Day7.h"
#include "utils.hpp"

CDay7::CDay7(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 7: Bridge Repair" } {}

enum EOperator
{
    Add = 0,
    Multiply,
    Concat
};

void CDay7::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input7-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    const auto lHasValidOperatorCombinationTask1 = [](std::ranges::forward_range auto aNumView) {
        const auto lTarget = *aNumView.begin();
        const auto lOperandsBegin = aNumView.begin() + 1;
        const auto lNumOfOperators = std::distance(lOperandsBegin, aNumView.end() - 1);
        const auto lNumOfCombinations = std::pow(2, lNumOfOperators);

        for (auto lFlags = 0; lFlags < lNumOfCombinations; lFlags++)
        {
            int lIndex = -1;
            const auto lSum = std::reduce(lOperandsBegin, aNumView.end(), 0ll, [&lIndex, &lFlags](int64_t aLhs, int64_t aRhs) {
                if (aLhs == 0)
                {
                    return aRhs;
                }

                lIndex++;
                return lFlags & (1 << lIndex) ? aLhs * aRhs : aLhs + aRhs;
            });

            if (lSum == lTarget)
            {
                return true;
            }
        }

        return false;
    };

    const auto lHasValidOperatorCombinationTask2 = [](std::ranges::forward_range auto aNumView) {
        const auto lTarget = *aNumView.begin();
        const auto lOperandsBegin = aNumView.begin() + 1;
        const auto lNumOfOperators = std::distance(lOperandsBegin, aNumView.end() - 1);
        const auto lNumOfCombinations = std::pow(3, lNumOfOperators);
        std::vector<EOperator> lOperators(lNumOfOperators, EOperator::Add);

        for (auto li = 0; li < lNumOfCombinations; li++)
        {
            int lIndex = -1;
            const auto lSum = std::reduce(lOperandsBegin, aNumView.end(), 0ll, [&lIndex, &lOperators](int64_t aLhs, int64_t aRhs) {
                if (aLhs == 0)
                {
                    return aRhs;
                }

                lIndex++;
                switch (lOperators[lIndex])
                {
                    case EOperator::Add:
                        return aLhs + aRhs;
                    case EOperator::Multiply:
                        return aLhs * aRhs;
                    case EOperator::Concat:
                        return concatNumbers(aLhs, aRhs);
                    default:
                        return 0ll;
                }
                });

            if (lSum == lTarget)
            {
                return true;
            }

            // Next combination
            for (auto lOperatorIndex = 0; lOperatorIndex < lNumOfOperators; lOperatorIndex++)
            {
                if (lOperators[lOperatorIndex] == EOperator::Concat)
                {
                    lOperators[lOperatorIndex] = EOperator::Add;
                    continue;
                }

                if (lOperators[lOperatorIndex] == EOperator::Add)
                {
                    lOperators[lOperatorIndex] = EOperator::Multiply;
                    break;
                }

                if (lOperators[lOperatorIndex] == EOperator::Multiply)
                {
                    lOperators[lOperatorIndex] = EOperator::Concat;
                    break;
                }
            }
        }

        return false;
    };

    auto lTask1View = lText
        | std::views::split(NEWLINE_DELIMITER)
        | std::ranges::views::transform([](auto aView) {
        auto lNums = getNumbersFromStringInt64(std::string_view{ aView });
        std::ranges::reverse(lNums);
            return lNums;
            })
        | std::ranges::views::filter([](const auto& aNumbers) {
            return !aNumbers.empty();
            })
        | std::ranges::views::filter(lHasValidOperatorCombinationTask1)
        | std::ranges::views::transform([](const auto& aView) {
            return *aView.begin();
            });

    auto lTask2View = lText
        | std::views::split(NEWLINE_DELIMITER)
        | std::ranges::views::transform([](auto aView) {
        auto lNums = getNumbersFromStringInt64(std::string_view{ aView });
        std::ranges::reverse(lNums);
        return lNums;
            })
        | std::ranges::views::filter([](const auto& aNumbers) {
        return !aNumbers.empty();
            })
        | std::ranges::views::filter(lHasValidOperatorCombinationTask2)
        | std::ranges::views::transform([](const auto& aView) {
        return *aView.begin();
            });

    std::cout << "Task 1: " << std::accumulate(lTask1View.begin(), lTask1View.end(), 0ll) << std::endl;
    std::cout << "Task 2: " << std::accumulate(lTask2View.begin(), lTask2View.end(), 0ll) << std::endl;

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
