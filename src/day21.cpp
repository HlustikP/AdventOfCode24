#include "day21.h"
#include "utils.hpp"

CDay21::CDay21(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 21: Insert Title" } {}

void CDay21::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input21-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
