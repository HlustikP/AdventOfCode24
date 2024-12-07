#pragma once

#include "AdventSolution.h"

class CDay17 final : public CAdventSolution {
public:
    explicit CDay17(const fs::path& aInputDir);
    ~CDay17() override = default;

    void solve() override;
};
