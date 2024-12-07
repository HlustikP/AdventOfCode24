#include "Day16.h"
#include "utils.hpp"

CDay16::CDay16(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 16: Insert Title" } {}

void CDay16::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input16-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
