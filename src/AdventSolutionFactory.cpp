#include "AdventSolutionFactory.h"

std::optional<std::unique_ptr<CAdventSolution>> CAdventSolutionFactory::create(const fs::path& aInputDir, const int aDay)
{
    switch (aDay)
    {
    case 1:
        return std::make_unique<CDay1>(aInputDir);
    case 2:
        return std::make_unique<CDay2>(aInputDir);
    case 3:
        return std::make_unique<CDay3>(aInputDir);
    case 4:
        return std::make_unique<CDay4>(aInputDir);
    default:
        return std::nullopt;
    }
}
