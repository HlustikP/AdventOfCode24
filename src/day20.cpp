#include "day20.h"
#include "utils.hpp"

CDay20::CDay20(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 20: Insert Title" } {}

void CDay20::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input20-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
