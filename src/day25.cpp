#include "day25.h"
#include "utils.hpp"

CDay25::CDay25(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 25: Insert Title" } {}

void CDay25::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input25-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
