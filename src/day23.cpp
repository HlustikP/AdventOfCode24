#include "day23.h"
#include "utils.hpp"

CDay23::CDay23(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 23: Insert Title" } {}

void CDay23::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input23-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
