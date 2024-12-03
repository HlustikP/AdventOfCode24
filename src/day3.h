#pragma once

#include "AdventSolution.h"

class CDay3 final : public CAdventSolution {
public:
    explicit CDay3(const fs::path& aInputDir);
    ~CDay3() override = default;

    void solve() override;
};
