#include "Day8.h"
#include "utils/misc.h"

CDay8::CDay8(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 8: Insert Title" } {}

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

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
