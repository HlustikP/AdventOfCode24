#include "day22.h"
#include "utils/misc.h"

CDay22::CDay22(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 22: Insert Title" } {}

void CDay22::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input22-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
