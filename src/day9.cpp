#include "Day9.h"
#include "utils/misc.h"

CDay9::CDay9(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 9: Insert Title" } {}

void CDay9::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input9-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    mEnd = std::chrono::high_resolution_clock::now();
    printTime();
}
