#include "Day18.h"
#include "utils.hpp"

CDay18::CDay18(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 18: Insert Title" } {}

void CDay18::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input18-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
