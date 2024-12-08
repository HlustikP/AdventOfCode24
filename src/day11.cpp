#include "Day11.h"
#include "utils/misc.h"

CDay11::CDay11(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 12: Insert Title" } {}

void CDay11::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input11-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
