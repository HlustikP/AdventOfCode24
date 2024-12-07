#include "Day14.h"
#include "utils.hpp"

CDay14::CDay14(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 14: Insert Title" } {}

void CDay14::solve()
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
