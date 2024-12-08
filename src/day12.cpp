#include "Day12.h"
#include "utils/misc.h"

CDay12::CDay12(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 12: Insert Title" } {}

void CDay12::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input12-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
