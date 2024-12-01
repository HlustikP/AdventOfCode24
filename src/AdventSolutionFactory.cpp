#include "AdventSolutionFactory.h"

std::optional<std::unique_ptr<CAdventSolution>> CAdventSolutionFactory::create(const fs::path& aInputDir, const int aDay)
{
    switch (aDay)
    {
    case 1:
        return std::make_unique<CDay1>(aInputDir);
    default:
        return std::nullopt;
    }
}