#include "Day6.h"
#include "utils.hpp"

CDay6::CDay6(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 6: Guard Gallivant" } {}

void CDay6::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input6-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
