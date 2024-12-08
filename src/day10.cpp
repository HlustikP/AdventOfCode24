#include "Day10.h"
#include "utils/misc.h"

CDay10::CDay10(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 10: Insert Title" } {}

void CDay10::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input10-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
