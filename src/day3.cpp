#include <regex>

#include "Day3.h"
#include "utils/misc.h"

constexpr auto DO_INSTRUCTION = "do()";
constexpr auto DONT_INSTRUCTION = "don't()";

CDay3::CDay3(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 3: Mull It Over" } {}

void CDay3::solve()
{
    printHeadline();

    auto lInput = loadFile("input3-1.txt");
    if (!lInput.has_value())
    {
        return;
    }

    mStart = std::chrono::high_resolution_clock::now();

    int64_t lSumTask1 = 0;
    int64_t lSumTask2 = 0;
    const auto& lText = lInput.value();

    const std::regex lMulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::smatch lMatch;
    auto lIterator = lText.begin();
    while (std::regex_search(lIterator, lText.end(), lMatch, lMulRegex)) {
        lSumTask1 += std::stoll(lMatch[1]) * std::stoll(lMatch[2]);

        // Move past the current match
        lIterator = lMatch.suffix().first;
    }

    // Prepend a do(), so I dont need a special case for the first match
    lInput.value().insert(0, "do()");

    lIterator = lText.begin();
    while (true) {
        const auto lPosition = std::distance(lText.begin(), lIterator);
        const auto lDoPos = lInput.value().find(DO_INSTRUCTION, lPosition);
        if (lDoPos == std::string::npos) {
            break;
        }

        size_t lDontPos = lPosition;
        while (true)
        {
            lDontPos = lInput.value().find(DONT_INSTRUCTION, lDontPos);
            // Wtb break out of outer loop feature :(
            if (lDontPos == std::string::npos) {
                break;
            }
            // Look for a dont() that is after the do()
            if (lDontPos > lDoPos) {
                break;
            }
            lDontPos = lDontPos + strlen(DONT_INSTRUCTION);
        }
        // Break out of outer loop
        if (lDontPos == std::string::npos) {
            break;
        }

        auto lRegexIterator = lText.begin() + lDoPos;
        while (std::regex_search(lRegexIterator, lText.begin() + lDontPos, lMatch, lMulRegex)) {
            lSumTask2 += std::stoll(lMatch[1]) * std::stoll(lMatch[2]);

            // Move past the current match
            lRegexIterator = lMatch.suffix().first;
        }

        lIterator = lText.begin() + lDontPos + strlen(DONT_INSTRUCTION);
    }

    mEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 Sum: " << lSumTask1 << std::endl;
    std::cout << "Task 2 Sum: " << lSumTask2 << std::endl;

    printTime();
}
