#include <ranges>
#include <unordered_set>

#include "Day8.h"
#include "utils/CGrid.h"
#include "utils/misc.h"

CDay8::CDay8(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 8: Resonant Collinearity" } {}

void CDay8::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input8-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();
    CGrid lGrid{ lText };
    std::unordered_set<CCell> lTask1Set;
    std::unordered_set<CCell> lTask2Set;

    for (char lChar = '0'; lChar <= 'z'; lChar++)
    {
        auto lCells = lGrid.getAllOccurrencesOf(lChar);
        if (lCells.empty())
        {
            continue;
        }

        auto lCellPairs = std::ranges::views::cartesian_product(lCells, lCells);
        for (const auto [lCell1, lCell2] : lCellPairs)
        {
            if (lCell1 == lCell2)
            {
                continue;
            }

            const auto lVec = lCell1 - lCell2;
            const auto lProjection = lGrid.moveWithVector(lCell1, lVec);
            if (lProjection.has_value())
            {
                lTask1Set.insert(lProjection.value());
            }
        }
    }

    for (char lChar = '0'; lChar <= 'z'; lChar++)
    {
        auto lCells = lGrid.getAllOccurrencesOf(lChar);
        if (lCells.empty())
        {
            continue;
        }

        auto lCellPairs = std::ranges::views::cartesian_product(lCells, lCells);
        for (const auto [lCell1, lCell2] : lCellPairs)
        {
            if (lCell1 == lCell2)
            {
                continue;
            }

            const auto lVec = lCell1 - lCell2;
            lTask2Set.insert(lCell1);

            auto lProjection = lGrid.moveWithVector(lCell1, lVec);
            while (lProjection.has_value())
            {
                lTask2Set.insert(lProjection.value());
                lProjection = lGrid.moveWithVector(lProjection.value(), lVec);
            }
        }
    }

    mEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Found " << lTask1Set.size() << " Task 1 antinodes" << std::endl;
    std::cout << "Found " << lTask2Set.size() << " Task 2 antinodes" << std::endl;

    printTime();
}
