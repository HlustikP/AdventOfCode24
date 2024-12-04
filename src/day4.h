#pragma once

#include "AdventSolution.h"

class CDay4 final : public CAdventSolution {
public:
    explicit CDay4(const fs::path& aInputDir);
    ~CDay4() override = default;

    void solve() override;
};
