#include "AdventSolutionFactory.h"

#define DAY_IMPLEMENTATION(DAY) \
    case DAY: \
        return std::make_unique<CDay##DAY>(aInputDir); \
        break;

std::optional<std::unique_ptr<CAdventSolution>> CAdventSolutionFactory::create(const fs::path& aInputDir, const int aDay)
{
    switch (aDay)
    {
        DAY_IMPLEMENTATION(1)
        DAY_IMPLEMENTATION(2)
        DAY_IMPLEMENTATION(3)
        DAY_IMPLEMENTATION(4)
        DAY_IMPLEMENTATION(5)
        DAY_IMPLEMENTATION(6)
        DAY_IMPLEMENTATION(7)
        DAY_IMPLEMENTATION(8)
        DAY_IMPLEMENTATION(9)
        DAY_IMPLEMENTATION(10)
        DAY_IMPLEMENTATION(11)
        DAY_IMPLEMENTATION(12)
        DAY_IMPLEMENTATION(13)
        DAY_IMPLEMENTATION(14)
        DAY_IMPLEMENTATION(15)
        DAY_IMPLEMENTATION(16)
        DAY_IMPLEMENTATION(17)
        DAY_IMPLEMENTATION(18)
        DAY_IMPLEMENTATION(19)
        DAY_IMPLEMENTATION(20)
        DAY_IMPLEMENTATION(21)
        DAY_IMPLEMENTATION(22)
        DAY_IMPLEMENTATION(23)
        DAY_IMPLEMENTATION(24)
        DAY_IMPLEMENTATION(25)
    default:
        return std::nullopt;
    }
}
