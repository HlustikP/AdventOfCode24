#include "Day17.h"
#include "utils.hpp"

CDay17::CDay17(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 17: Insert Title" } {}

void CDay17::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input17-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
