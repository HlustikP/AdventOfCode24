#include "Day13.h"
#include "utils/misc.h"

CDay13::CDay13(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 13: Insert Title" } {}

void CDay13::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input13-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
