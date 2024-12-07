#pragma once

#include "AdventSolution.h"

class CDay24 final : public CAdventSolution {
public:
    explicit CDay24(const fs::path& aInputDir);
    ~CDay24() override = default;

    void solve() override;
};
