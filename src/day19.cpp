#include "Day19.h"
#include "utils.hpp"

CDay19::CDay19(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 19: Insert Title" } {}

void CDay19::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input19-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
