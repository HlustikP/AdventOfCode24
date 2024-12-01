#pragma once

#include "pch.h"

#include <optional>

class CAdventSolutionFactory
{
public:
    static std::optional<std::unique_ptr<CAdventSolution>> create(const fs::path& aInputDir, const int aDay);
};
