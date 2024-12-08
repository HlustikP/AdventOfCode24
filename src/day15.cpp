#include "Day15.h"
#include "utils/misc.h"

CDay15::CDay15(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 15: Insert Title" } {}

void CDay15::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input15-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
