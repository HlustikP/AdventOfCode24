#include "day24.h"
#include "utils/misc.h"

CDay24::CDay24(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 24: Insert Title" } {}

void CDay24::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input24-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
